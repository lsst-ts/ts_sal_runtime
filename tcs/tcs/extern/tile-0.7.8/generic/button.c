/* button.c,v 1.48 2006/08/04 23:22:50 patthoyts Exp
 * Copyright (c) 2003, Joe English
 *
 * Tile widget set: label, button, checkbutton, radiobutton, and 
 * menubutton widgets.
 */

#include <string.h>
#include <tk.h>
#include "tkTheme.h"
#include "widget.h"

/* Bit fields for OptionSpec mask field:
 */
#define STATE_CHANGED	 	(0x100)		/* -state option changed */
#define DEFAULTSTATE_CHANGED	(0x200)		/* -default option changed */

/*------------------------------------------------------------------------
 * +++ Base resources for labels, buttons, checkbuttons, etc:
 */
typedef struct
{
    /*
     * Text element resources:
     */
    Tcl_Obj *textObj;
    Tcl_Obj *textVariableObj;
    Tcl_Obj *underlineObj;
    Tcl_Obj *widthObj;

    Ttk_TraceHandle	*textVariableTrace;
    Tk_Image	*images;

    /*
     * Image element resources:
     */
    Tcl_Obj *imageObj;

    /*
     * Compound label/image resources:
     */
    Tcl_Obj *compoundObj;
    Tcl_Obj *paddingObj;

    /*
     * Compatibility/legacy options:
     */
    Tcl_Obj *stateObj;

} BasePart;

typedef struct
{
    WidgetCore	core;
    BasePart	base;
} Base;

static Tk_OptionSpec BaseOptionSpecs[] =
{
    {TK_OPTION_STRING, "-text", "text", "Text", "",
	Tk_Offset(Base,base.textObj), -1, 
	0,0,GEOMETRY_CHANGED },
    {TK_OPTION_STRING, "-textvariable", "textVariable", "Variable", "",
	Tk_Offset(Base,base.textVariableObj), -1, 
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },
    {TK_OPTION_INT, "-underline", "underline", "Underline",
	"-1", Tk_Offset(Base,base.underlineObj), -1, 
	0,0,0 },
    /* SB: OPTION_INT, see <<NOTE-NULLOPTIONS>> */
    {TK_OPTION_STRING, "-width", "width", "Width",
	NULL, Tk_Offset(Base,base.widthObj), -1, 
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },

    /*
     * Image options
     */
    {TK_OPTION_STRING, "-image", "image", "Image", NULL/*default*/,
	Tk_Offset(Base,base.imageObj), -1, 
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },

    /*
     * Compound base/image options
     */
    {TK_OPTION_STRING_TABLE, "-compound", "compound", "Compound",
	 "none", Tk_Offset(Base,base.compoundObj), -1,
	 0,(ClientData)TTKCompoundStrings,GEOMETRY_CHANGED },
    {TK_OPTION_STRING, "-padding", "padding", "Pad",
	NULL, Tk_Offset(Base,base.paddingObj), -1,
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED},

    /*
     * Compatibility/legacy options
     */
    {TK_OPTION_STRING, "-state", "state", "State",
	 "normal", Tk_Offset(Base,base.stateObj), -1,
	 0,0,STATE_CHANGED },

    WIDGET_INHERIT_OPTIONS(CoreOptionSpecs)
};

/*
 * Variable trace procedure for -textvariable option:
 */
static void TextVariableChanged(void *clientData, const char *value)
{
    Base *basePtr = clientData;
    Tcl_Obj *newText;

    if (WidgetDestroyed(&basePtr->core)) {
	return;
    }

    newText = value ? Tcl_NewStringObj(value, -1) : Tcl_NewStringObj("", 0);

    Tcl_IncrRefCount(newText);
    Tcl_DecrRefCount(basePtr->base.textObj);
    basePtr->base.textObj = newText;

    TtkResizeWidget(&basePtr->core);
}

/*
 * Tk_ImageChangedProc for -image option:
 */
static void CoreImageChangedProc(ClientData clientData,
    int x, int y, int width, int height, int imageWidth, int imageHeight)
{
    WidgetCore *corePtr = (WidgetCore *)clientData;
    TtkRedisplayWidget(corePtr);
}

/* GetImageList --
 * 	ConfigureProc utility routine for handling -image option.
 * 	Verifies that -image is a valid image specification,
 * 	registers image-changed callbacks for each image (via Tk_GetImage).
 *
 * 	The -image option is a multi-element list; the first element
 * 	is the name of the default image to use, the remainder of the 
 * 	list is a sequence of statespec/imagename options as per 
 * 	[style map].
 *
 * Returns: TCL_OK if image specification is valid and sets *imageListPtr
 * 	to a NULL-terminated list of Tk_Images; otherwise TCL_ERROR
 * 	and leaves an error message in the interpreter result.
 */
int GetImageList(
    Tcl_Interp *interp, 
    WidgetCore *corePtr, 
    Tcl_Obj *imageOption, 
    Tk_Image **imageListPtr)
{
    int i, mapCount, imageCount;
    Tcl_Obj **mapList;
    Tk_Image *images;

    if (Tcl_ListObjGetElements(interp, 
		imageOption, &mapCount, &mapList) != TCL_OK) 
    {
	return TCL_ERROR;
    }

    if (mapCount == 0) {
	*imageListPtr = 0;
	return TCL_OK;
    }

    if ((mapCount % 2) != 1) {
	Tcl_SetResult(interp,
	    "-image value must contain an odd number of elements", TCL_STATIC);
	return TCL_ERROR;
    }

    /* Verify state specifications:
     */
    for (i = 1; i < mapCount -1; i += 2) {
	Ttk_StateSpec spec;
	if (Ttk_GetStateSpecFromObj(interp, mapList[i], &spec) != TCL_OK)
	    return TCL_ERROR;
    }
    
    /* Get images:
     */
    imageCount = (mapCount + 1) / 2;
    images = (Tk_Image*)ckalloc((imageCount+1) * sizeof(Tk_Image));

    for (i = 0; i < imageCount; ++i) {
	const char *imageName = Tcl_GetString(mapList[i * 2]);
	images[i] = Tk_GetImage(interp, corePtr->tkwin, 
		imageName, CoreImageChangedProc, corePtr);

	if (!images[i]) {
	    while (i--)
		Tk_FreeImage(images[i]);
	    ckfree((ClientData)images);
	    return TCL_ERROR;
	}
    }
    images[i] = NULL;	/* Add null terminator */

    *imageListPtr = images;
    return TCL_OK;
}

/*
 * FreeImageList --
 * 	Release an image list obtained by GetImageList.
 */
void FreeImageList(Tk_Image *imageList)
{
    Tk_Image *p;
    for (p = imageList; *p; ++p)
	Tk_FreeImage(*p);
    ckfree((ClientData)imageList);
}

static int
BaseInitialize(Tcl_Interp *interp, void *recordPtr)
{
    Base *basePtr = recordPtr;
    basePtr->base.textVariableTrace = 0;
    basePtr->base.images = NULL;
    return TCL_OK;
}

static void
BaseCleanup(void *recordPtr)
{
    Base *basePtr = recordPtr;
    if (basePtr->base.textVariableTrace)
	Ttk_UntraceVariable(basePtr->base.textVariableTrace);
    if (basePtr->base.images) 
    	FreeImageList(basePtr->base.images);
}

static int BaseConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Base *basePtr = recordPtr;
    Tcl_Obj *textVarName = basePtr->base.textVariableObj;
    Ttk_TraceHandle *vt = 0;
    Tk_Image *images = NULL;

    if (textVarName != NULL && *Tcl_GetString(textVarName) != '\0') {
	vt = Ttk_TraceVariable(interp,textVarName,TextVariableChanged,basePtr);
	if (!vt) return TCL_ERROR;
    }

    if (basePtr->base.imageObj && GetImageList(interp, 
		&basePtr->core, basePtr->base.imageObj, &images) != TCL_OK)
    {
	goto error;
    }

    if (CoreConfigure(interp, recordPtr, mask) != TCL_OK) {
error:
	if (images) FreeImageList(images);
	if (vt) Ttk_UntraceVariable(vt);
	return TCL_ERROR;
    }

    if (basePtr->base.textVariableTrace) {
	Ttk_UntraceVariable(basePtr->base.textVariableTrace);
    }
    basePtr->base.textVariableTrace = vt;

    if (basePtr->base.images) {
	FreeImageList(basePtr->base.images);
    }
    basePtr->base.images = images;

    if (mask & STATE_CHANGED) {
	CheckStateOption(&basePtr->core, basePtr->base.stateObj);
    }

    return TCL_OK;
}

static int
BasePostConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Base *basePtr = recordPtr;
    int status = TCL_OK;

    if (basePtr->base.textVariableTrace) {
	status = Ttk_FireTrace(basePtr->base.textVariableTrace);
    }

    return status;
}


/*------------------------------------------------------------------------
 * +++ Label widget:
 * Just a base widget that adds a few appearance-related options
 */

typedef struct
{
    Tcl_Obj *backgroundObj;
    Tcl_Obj *foregroundObj;
    Tcl_Obj *fontObj;
    Tcl_Obj *borderWidthObj;
    Tcl_Obj *reliefObj;
    Tcl_Obj *anchorObj;
    Tcl_Obj *justifyObj;
    Tcl_Obj *wrapLengthObj;
} LabelPart;

typedef struct
{
    WidgetCore	core;
    BasePart	base;
    LabelPart	label;
} Label;

static Tk_OptionSpec LabelOptionSpecs[] =
{
    {TK_OPTION_BORDER, "-background", "frameColor", "FrameColor", 
	NULL, Tk_Offset(Label,label.backgroundObj), -1,
	TK_OPTION_NULL_OK,0,0 },
    {TK_OPTION_COLOR, "-foreground", "textColor", "TextColor", 
	NULL, Tk_Offset(Label,label.foregroundObj), -1,
	TK_OPTION_NULL_OK,0,0 },
    {TK_OPTION_FONT, "-font", "font", "Font",
	NULL, Tk_Offset(Label,label.fontObj), -1,
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },
    {TK_OPTION_PIXELS, "-borderwidth", "borderWidth", "BorderWidth", 
	NULL, Tk_Offset(Label,label.borderWidthObj), -1,
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },
    {TK_OPTION_RELIEF, "-relief", "relief", "Relief",
	NULL, Tk_Offset(Label,label.reliefObj), -1,
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },
    {TK_OPTION_ANCHOR, "-anchor", "anchor", "Anchor",
	NULL, Tk_Offset(Label,label.anchorObj), -1, 
	TK_OPTION_NULL_OK, 0, GEOMETRY_CHANGED},
    {TK_OPTION_JUSTIFY, "-justify", "justify", "Justify",
	NULL, Tk_Offset(Label, label.justifyObj), -1,
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED },
    {TK_OPTION_PIXELS, "-wraplength", "wrapLength", "WrapLength",
	NULL, Tk_Offset(Label, label.wrapLengthObj), -1,
	TK_OPTION_NULL_OK,0,GEOMETRY_CHANGED /*SB: SIZE_CHANGED*/ },

    WIDGET_INHERIT_OPTIONS(BaseOptionSpecs)
};

static WidgetCommandSpec LabelCommands[] =
{
    { "configure",	WidgetConfigureCommand },
    { "cget",		WidgetCgetCommand },
    { "instate",	WidgetInstateCommand },
    { "state",  	WidgetStateCommand },
    { "identify",	WidgetIdentifyCommand },
    { NULL, NULL }
};

WidgetSpec LabelWidgetSpec =
{
    "TLabel",			/* className */
    sizeof(Label),		/* recordSize */
    LabelOptionSpecs,		/* optionSpecs */
    LabelCommands,		/* subcommands */
    BaseInitialize,		/* initializeProc */
    BaseCleanup,		/* cleanupProc */
    BaseConfigure,		/* configureProc */
    BasePostConfigure,		/* postConfigureProc */
    WidgetGetLayout, 		/* getLayoutProc */
    WidgetSize, 		/* sizeProc */
    WidgetDoLayout,		/* layoutProc */
    WidgetDisplay		/* displayProc */
};

/*------------------------------------------------------------------------
 * +++ Button widget.
 * Adds a new subcommand "invoke", and options "-command" and "-default"
 */

typedef struct
{
    Tcl_Obj *commandObj;
    Tcl_Obj *defaultStateObj;
} ButtonPart;

typedef struct
{
    WidgetCore	core;
    BasePart	base;
    ButtonPart	button;
} Button;

/*
 * Option specifications:
 */
static Tk_OptionSpec ButtonOptionSpecs[] =
{
    WIDGET_TAKES_FOCUS,

    {TK_OPTION_STRING, "-command", "command", "Command",
	"", Tk_Offset(Button, button.commandObj), -1, 0,0,0},
    {TK_OPTION_STRING_TABLE, "-default", "default", "Default",
	"normal", Tk_Offset(Button, button.defaultStateObj), -1,
	0, (ClientData) TTKDefaultStrings, DEFAULTSTATE_CHANGED},

    WIDGET_INHERIT_OPTIONS(BaseOptionSpecs)
};

static int ButtonConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Button *buttonPtr = recordPtr;

    if (BaseConfigure(interp, recordPtr, mask) != TCL_OK) {
	return TCL_ERROR;
    }

    /* Handle "-default" option:
     */
    if (mask & DEFAULTSTATE_CHANGED) {
	int defaultState = TTK_BUTTON_DEFAULT_DISABLED;
	Ttk_GetButtonDefaultStateFromObj(
	    NULL, buttonPtr->button.defaultStateObj, &defaultState);
	if (defaultState == TTK_BUTTON_DEFAULT_ACTIVE) {
	    WidgetChangeState(&buttonPtr->core, TTK_STATE_ALTERNATE, 0);
	} else {
	    WidgetChangeState(&buttonPtr->core, 0, TTK_STATE_ALTERNATE);
	}
    }
    return TCL_OK;
}

/* $button invoke --
 * 	Evaluate the button's -command.
 */
static int
ButtonInvokeCommand(
    Tcl_Interp *interp, int objc, Tcl_Obj *const objv[], void *recordPtr)
{
    Button *buttonPtr = recordPtr;
    if (objc > 2) {
	Tcl_WrongNumArgs(interp, 1, objv, "invoke");
	return TCL_ERROR;
    }
    if (buttonPtr->core.state & TTK_STATE_DISABLED) {
	return TCL_OK;
    }
    return Tcl_EvalObjEx(interp, buttonPtr->button.commandObj, TCL_EVAL_GLOBAL);
}

static WidgetCommandSpec ButtonCommands[] =
{
    { "configure",	WidgetConfigureCommand },
    { "cget",		WidgetCgetCommand },
    { "invoke",		ButtonInvokeCommand },
    { "instate",	WidgetInstateCommand },
    { "state",  	WidgetStateCommand },
    { "identify",	WidgetIdentifyCommand },
    { NULL, NULL }
};

WidgetSpec ButtonWidgetSpec =
{
    "TButton",			/* className */
    sizeof(Button),		/* recordSize */
    ButtonOptionSpecs,		/* optionSpecs */
    ButtonCommands,		/* subcommands */
    BaseInitialize,		/* initializeProc */
    BaseCleanup,		/* cleanupProc */
    ButtonConfigure,		/* configureProc */
    BasePostConfigure,		/* postConfigureProc */
    WidgetGetLayout, 		/* getLayoutProc */
    WidgetSize, 		/* sizeProc */
    WidgetDoLayout,		/* layoutProc */
    WidgetDisplay		/* displayProc */
};

/*------------------------------------------------------------------------
 * +++ Checkbutton widget.
 */
typedef struct
{
    Tcl_Obj *variableObj;
    Tcl_Obj *onValueObj;
    Tcl_Obj *offValueObj;
    Tcl_Obj *commandObj;

    Ttk_TraceHandle *variableTrace;

} CheckbuttonPart;

typedef struct
{
    WidgetCore core;
    BasePart base;
    CheckbuttonPart checkbutton;
} Checkbutton;

/*
 * Option specifications:
 */
static Tk_OptionSpec CheckbuttonOptionSpecs[] =
{
    WIDGET_TAKES_FOCUS,

    {TK_OPTION_STRING, "-variable", "variable", "Variable",
	"", Tk_Offset(Checkbutton, checkbutton.variableObj), -1, 0,0,0},
    {TK_OPTION_STRING, "-onvalue", "onValue", "OnValue",
	"1", Tk_Offset(Checkbutton, checkbutton.onValueObj), -1, 0,0,0},
    {TK_OPTION_STRING, "-offvalue", "offValue", "OffValue",
	"0", Tk_Offset(Checkbutton, checkbutton.offValueObj), -1, 0,0,0},
    {TK_OPTION_STRING, "-command", "command", "Command",
	"", Tk_Offset(Checkbutton, checkbutton.commandObj), -1, 0,0,0},

    WIDGET_INHERIT_OPTIONS(BaseOptionSpecs)
};

/*
 * Variable trace procedure for checkbutton -variable option
 */
static void CheckbuttonVariableChanged(void *clientData, const char *value)
{
    Checkbutton *checkPtr = clientData;

    if (WidgetDestroyed(&checkPtr->core)) {
	return;
    }

    if (!value) {
	WidgetChangeState(&checkPtr->core, TTK_STATE_ALTERNATE, 0);
	return;
    }
    /* else */
    WidgetChangeState(&checkPtr->core, 0, TTK_STATE_ALTERNATE);
    if (!strcmp(value, Tcl_GetString(checkPtr->checkbutton.onValueObj))) {
	WidgetChangeState(&checkPtr->core, TTK_STATE_SELECTED, 0);
    } else {
	WidgetChangeState(&checkPtr->core, 0, TTK_STATE_SELECTED);
    }
}

static int CheckbuttonInitialize(Tcl_Interp *interp, void *recordPtr)
{
    Checkbutton *checkPtr = recordPtr;
    Tcl_Obj *objPtr;

    /* default -variable is the widget name:
     */
    objPtr = Tcl_NewStringObj(Tk_PathName(checkPtr->core.tkwin), -1);
    Tcl_IncrRefCount(objPtr);
    Tcl_DecrRefCount(checkPtr->checkbutton.variableObj);
    checkPtr->checkbutton.variableObj = objPtr;

    return BaseInitialize(interp, recordPtr);
}

static void
CheckbuttonCleanup(void *recordPtr)
{
    Checkbutton *checkPtr = recordPtr;
    Ttk_UntraceVariable(checkPtr->checkbutton.variableTrace);
    checkPtr->checkbutton.variableTrace = 0;
    BaseCleanup(recordPtr);
}

static int
CheckbuttonConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Checkbutton *checkPtr = recordPtr;
    Ttk_TraceHandle *vt = Ttk_TraceVariable(
	interp, checkPtr->checkbutton.variableObj,
	CheckbuttonVariableChanged, checkPtr);

    if (!vt) {
	return TCL_ERROR;
    }

    if (BaseConfigure(interp, recordPtr, mask) != TCL_OK){
	Ttk_UntraceVariable(vt);
	return TCL_ERROR;
    }

    Ttk_UntraceVariable(checkPtr->checkbutton.variableTrace);
    checkPtr->checkbutton.variableTrace = vt;

    return TCL_OK;
}

static int
CheckbuttonPostConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Checkbutton *checkPtr = recordPtr;
    int status = TCL_OK;

    if (checkPtr->checkbutton.variableTrace)
	status = Ttk_FireTrace(checkPtr->checkbutton.variableTrace);
    if (status == TCL_OK && !WidgetDestroyed(&checkPtr->core))
	status = BasePostConfigure(interp, recordPtr, mask);
    return status;
}

/*
 * Checkbutton 'invoke' subcommand:
 * 	Toggles the checkbutton state.
 */
static int
CheckbuttonInvokeCommand(
    Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[], void *recordPtr)
{
    Checkbutton *checkPtr = recordPtr;
    WidgetCore *corePtr = &checkPtr->core;
    Tcl_Obj *newValue;

    if (objc > 2) {
	Tcl_WrongNumArgs(interp, 1, objv, "invoke");
	return TCL_ERROR;
    }
    if (corePtr->state & TTK_STATE_DISABLED)
	return TCL_OK;

    /*
     * Toggle the selected state.
     */
    if (corePtr->state & TTK_STATE_SELECTED)
	newValue = checkPtr->checkbutton.offValueObj;
    else
	newValue = checkPtr->checkbutton.onValueObj;

    if (Tcl_ObjSetVar2(interp,
	    checkPtr->checkbutton.variableObj, NULL, newValue,
	    TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG)
	== NULL)
	return TCL_ERROR;

    if (WidgetDestroyed(corePtr))
	return TCL_ERROR;

    return Tcl_EvalObjEx(interp,
	checkPtr->checkbutton.commandObj, TCL_EVAL_GLOBAL);
}

static WidgetCommandSpec CheckbuttonCommands[] =
{
    { "configure",	WidgetConfigureCommand },
    { "cget",		WidgetCgetCommand },
    { "invoke",		CheckbuttonInvokeCommand },
    { "instate",	WidgetInstateCommand },
    { "state",  	WidgetStateCommand },
    { "identify",	WidgetIdentifyCommand },
    /* MISSING: select, deselect, toggle */
    { NULL, NULL }
};

WidgetSpec CheckbuttonWidgetSpec =
{
    "TCheckbutton",		/* className */
    sizeof(Checkbutton),	/* recordSize */
    CheckbuttonOptionSpecs,	/* optionSpecs */
    CheckbuttonCommands,	/* subcommands */
    CheckbuttonInitialize,	/* initializeProc */
    CheckbuttonCleanup,		/* cleanupProc */
    CheckbuttonConfigure,	/* configureProc */
    CheckbuttonPostConfigure,	/* postConfigureProc */
    WidgetGetLayout, 		/* getLayoutProc */
    WidgetSize, 		/* sizeProc */
    WidgetDoLayout,		/* layoutProc */
    WidgetDisplay		/* displayProc */
};

/*------------------------------------------------------------------------
 * +++ Radiobutton widget.
 */

typedef struct
{
    Tcl_Obj *variableObj;
    Tcl_Obj *valueObj;
    Tcl_Obj *commandObj;

    Ttk_TraceHandle	*variableTrace;

} RadiobuttonPart;

typedef struct
{
    WidgetCore core;
    BasePart base;
    RadiobuttonPart radiobutton;
} Radiobutton;

/*
 * Option specifications:
 */
static Tk_OptionSpec RadiobuttonOptionSpecs[] =
{
    WIDGET_TAKES_FOCUS,

    {TK_OPTION_STRING, "-variable", "variable", "Variable",
	"::selectedButton", Tk_Offset(Radiobutton, radiobutton.variableObj),-1,
	0,0,0},
    {TK_OPTION_STRING, "-value", "Value", "Value",
	"1", Tk_Offset(Radiobutton, radiobutton.valueObj), -1,
	0,0,0},
    {TK_OPTION_STRING, "-command", "command", "Command",
	"", Tk_Offset(Radiobutton, radiobutton.commandObj), -1,
	0,0,0},

    WIDGET_INHERIT_OPTIONS(BaseOptionSpecs)
};

/*
 * Variable trace procedure for radiobuttons.
 */
static void 
RadiobuttonVariableChanged(void *clientData, const char *value)
{
    Radiobutton *radioPtr = clientData;

    if (WidgetDestroyed(&radioPtr->core)) {
	return;
    }

    if (!value) {
	WidgetChangeState(&radioPtr->core, TTK_STATE_ALTERNATE, 0);
	return;
    }
    /* else */
    WidgetChangeState(&radioPtr->core, 0, TTK_STATE_ALTERNATE);
    if (!strcmp(value, Tcl_GetString(radioPtr->radiobutton.valueObj))) {
	WidgetChangeState(&radioPtr->core, TTK_STATE_SELECTED, 0);
    } else {
	WidgetChangeState(&radioPtr->core, 0, TTK_STATE_SELECTED);
    }
}

static void
RadiobuttonCleanup(void *recordPtr)
{
    Radiobutton *radioPtr = recordPtr;
    Ttk_UntraceVariable(radioPtr->radiobutton.variableTrace);
    radioPtr->radiobutton.variableTrace = 0;
    BaseCleanup(recordPtr);
}

static int
RadiobuttonConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Radiobutton *radioPtr = recordPtr;
    Ttk_TraceHandle *vt = Ttk_TraceVariable(
	interp, radioPtr->radiobutton.variableObj,
	RadiobuttonVariableChanged, radioPtr);

    if (!vt) {
	return TCL_ERROR;
    }

    if (BaseConfigure(interp, recordPtr, mask) != TCL_OK) {
	Ttk_UntraceVariable(vt);
	return TCL_ERROR;
    }

    Ttk_UntraceVariable(radioPtr->radiobutton.variableTrace);
    radioPtr->radiobutton.variableTrace = vt;

    return TCL_OK;
}

static int
RadiobuttonPostConfigure(Tcl_Interp *interp, void *recordPtr, int mask)
{
    Radiobutton *radioPtr = recordPtr;
    int status = TCL_OK;

    if (radioPtr->radiobutton.variableTrace)
	status = Ttk_FireTrace(radioPtr->radiobutton.variableTrace);
    if (status == TCL_OK && !WidgetDestroyed(&radioPtr->core))
	status = BasePostConfigure(interp, recordPtr, mask);
    return status;
}

/*
 * Radiobutton 'invoke' subcommand:
 * 	Sets the radiobutton -variable to the -value, evaluates the -command.
 */
static int
RadiobuttonInvokeCommand(
    Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[], void *recordPtr)
{
    Radiobutton *radioPtr = recordPtr;
    WidgetCore *corePtr = &radioPtr->core;

    if (objc > 2) {
	Tcl_WrongNumArgs(interp, 1, objv, "invoke");
	return TCL_ERROR;
    }
    if (corePtr->state & TTK_STATE_DISABLED)
	return TCL_OK;

    if (Tcl_ObjSetVar2(interp,
	    radioPtr->radiobutton.variableObj, NULL,
	    radioPtr->radiobutton.valueObj,
	    TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG)
	== NULL)
	return TCL_ERROR;

    if (WidgetDestroyed(corePtr))
	return TCL_ERROR;

    return Tcl_EvalObjEx(interp,
	radioPtr->radiobutton.commandObj, TCL_EVAL_GLOBAL);
}

static WidgetCommandSpec RadiobuttonCommands[] =
{
    { "configure",	WidgetConfigureCommand },
    { "cget",		WidgetCgetCommand },
    { "invoke",		RadiobuttonInvokeCommand },
    { "instate",	WidgetInstateCommand },
    { "state",  	WidgetStateCommand },
    { "identify",	WidgetIdentifyCommand },
    /* MISSING: select, deselect */
    { NULL, NULL }
};

WidgetSpec RadiobuttonWidgetSpec =
{
    "TRadiobutton",		/* className */
    sizeof(Radiobutton),	/* recordSize */
    RadiobuttonOptionSpecs,	/* optionSpecs */
    RadiobuttonCommands,	/* subcommands */
    BaseInitialize,		/* initializeProc */
    RadiobuttonCleanup,		/* cleanupProc */
    RadiobuttonConfigure,	/* configureProc */
    RadiobuttonPostConfigure,	/* postConfigureProc */
    WidgetGetLayout, 		/* getLayoutProc */
    WidgetSize, 		/* sizeProc */
    WidgetDoLayout,		/* layoutProc */
    WidgetDisplay		/* displayProc */
};

/*------------------------------------------------------------------------
 * +++ Menubutton widget.
 */

typedef struct
{
    Tcl_Obj *menuObj;
    Tcl_Obj *directionObj;
} MenubuttonPart;

typedef struct
{
    WidgetCore core;
    BasePart base;
    MenubuttonPart menubutton;
} Menubutton;

/*
 * Option specifications:
 */
static const char *directionStrings[] = {
    "above", "below", "left", "right", "flush", NULL
};
static Tk_OptionSpec MenubuttonOptionSpecs[] =
{
    WIDGET_TAKES_FOCUS,

    {TK_OPTION_STRING, "-menu", "menu", "Menu",
	"", Tk_Offset(Menubutton, menubutton.menuObj), -1, 0,0,0},
    {TK_OPTION_STRING_TABLE, "-direction", "direction", "Direction",
	"below", Tk_Offset(Menubutton, menubutton.directionObj), -1,
	0,(ClientData)directionStrings,GEOMETRY_CHANGED},

    WIDGET_INHERIT_OPTIONS(BaseOptionSpecs)
};

static WidgetCommandSpec MenubuttonCommands[] =
{
    { "configure",	WidgetConfigureCommand },
    { "cget",		WidgetCgetCommand },
    { "instate",	WidgetInstateCommand },
    { "state",  	WidgetStateCommand },
    { "identify",	WidgetIdentifyCommand },
    { NULL, NULL }
};

WidgetSpec MenubuttonWidgetSpec =
{
    "TMenubutton",		/* className */
    sizeof(Menubutton), 	/* recordSize */
    MenubuttonOptionSpecs, 	/* optionSpecs */
    MenubuttonCommands,  	/* subcommands */
    BaseInitialize,     	/* initializeProc */
    BaseCleanup,		/* cleanupProc */
    BaseConfigure,		/* configureProc */
    BasePostConfigure,  	/* postConfigureProc */
    WidgetGetLayout, 		/* getLayoutProc */
    WidgetSize, 		/* sizeProc */
    WidgetDoLayout,		/* layoutProc */
    WidgetDisplay		/* displayProc */
};

