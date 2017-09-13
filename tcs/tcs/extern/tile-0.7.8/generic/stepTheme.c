/* stepTheme.c - Copyright (C) 2003 Pat Thoyts <patthoyts@users.sf.net>
 *
 * A OpenStep/NeXTStep style theme.
 *
 * This illustrates the need to be able to adjust the widget layout per
 * style engine.
 *
 */

#include <tk.h>
#include "tkTheme.h"

/* ---------------------------------------------------------------------- */

#define DEFAULT_BORDERWIDTH "2"

static GC 
GetBlackGC(Tk_Window tkwin)
{
    XGCValues gcvalues;
    gcvalues.foreground = BlackPixelOfScreen(Tk_Screen(tkwin));
    return Tk_GetGC(tkwin, GCForeground, &gcvalues);
}

#ifdef PAT_EXPERIMENTAL
static GC 
GetWhiteGC(Tk_Window tkwin)
{
    XGCValues gcvalues;
    gcvalues.foreground = WhitePixelOfScreen(Tk_Screen(tkwin));
    return Tk_GetGC(tkwin, GCForeground, &gcvalues);
}

static void
DrawRing(Display *display, Drawable d, GC gc, int x, int y, int a, int b, int i)
{
    XPoint pt[10];
    int n = 0;
    pt[n].x = x + a + i;  pt[n++].y = y + i;
    pt[n].x = b;      pt[n++].y = 0;
    pt[n].x = a;      pt[n++].y = a;
    pt[n].x = 0;      pt[n++].y = b;
    pt[n].x = -a;     pt[n++].y = a;
    pt[n].x = -b;     pt[n++].y = 0;
    pt[n].x = -a;     pt[n++].y = -a;
    pt[n].x = 0;      pt[n++].y = -b;
    pt[n].x = a;      pt[n++].y = -a;
    XDrawLines(display, d, gc, pt, n, CoordModePrevious);
    if (! (i & 1)) {
	pt[0].x = x + i + a + b - 1;  pt[0].y = y + i;
	pt[1].x = x + i + a + b + a;  pt[1].y = y + i + a + 1;
	XDrawLines(display, d, gc, pt, 2, CoordModeOrigin);
	pt[0].x = x + i + a + b - 1;  pt[0].y = y + i + a + b + a;
	pt[1].x = x + i + a + b + a;  pt[1].y = y + i + a + b - 1;
	XDrawLines(display, d, gc, pt, 2, CoordModeOrigin);
	pt[1].x = x + i + a + 1;  pt[1].y = y + i;
	pt[0].x = x + i;          pt[0].y = y + i + a + 1;
	XDrawLines(display, d, gc, pt, 2, CoordModeOrigin);
	pt[0].x = x + i;          pt[0].y = y + i + a + b - 1;
	pt[1].x = x + i + a + 1;  pt[1].y = y + i + a + b + a;
	XDrawLines(display, d, gc, pt, 2, CoordModeOrigin);
    }
}

static void
Draw3DCircle(Tk_Window tkwin, Drawable d, int x, int y, int diameter, Tk_3DBorder border)
{
    GC gcLight, gcDark, gcBlack;
    Display *display = Tk_Display(tkwin);
    
    diameter = diameter | 1;

    gcLight = Tk_3DBorderGC(tkwin, border, TK_3D_LIGHT_GC);
    gcDark = Tk_3DBorderGC(tkwin, border, TK_3D_DARK_GC);
    gcBlack = GetBlackGC(tkwin);
    
    XFillArc(display, d, gcLight, x, y, 
	(unsigned)diameter, (unsigned)diameter, 0, 360*64);
    DrawRing(display, d, gcDark, x, y, 3, 7, 0); /* ring - 0 */
    DrawRing(display, d, gcBlack, x, y, 3, 5, 1); /* ring - 1 */
#if 0
    DrawRing(display, d, gcDark,  x, y, 2, 5, 2); /* ring - 2 */
    DrawRing(display, d, gcBlack, x, y, 2, 3, 3); /* ring - 3 */
    DrawRing(display, d, gcDark,  x, y, 1, 3, 4); /* ring - 4 */
    DrawRing(display, d, gcBlack, x, y, 1, 1, 5); /* ring - 5 */

    XDrawArc(display, d, gcDark,  x, y, diameter, diameter, 30*64, 210*64 /*0, 360*64*/);
    XDrawArc(display, d, gcBlack, x+1, y+1, diameter-1, diameter-1, 30*64, 210*64);

    XDrawArc(display, d, gcLight, x+1, y+1, diameter-2, diameter-2, 30*64, 210*64);
    XDrawArc(display, d, gcDark, x-1, y-1, diameter-2, diameter-2, 230*64, 170*64);
#endif
    Tk_FreeGC(Tk_Display(tkwin), gcBlack);
}
#endif /*PAT_EXPERIMENTAL*/

/*
 *----------------------------------------------------------------------
 * 
 * DrawCheckMark -- 
 *
 *	Draw an OPENSTEP style check indicator. This is a 8x8 3D tick.
 *
 *----------------------------------------------------------------------
 */

static void
DrawCheckMark(Tk_Window tkwin, Drawable d, int x, int y, Tk_3DBorder border)
{
    GC gcLight, gcDark, gcBlack;
    Display *display = Tk_Display(tkwin);
    
    gcBlack = GetBlackGC(tkwin);
    gcLight = Tk_3DBorderGC(tkwin, border, TK_3D_LIGHT_GC);
    gcDark  = Tk_3DBorderGC(tkwin, border, TK_3D_DARK_GC);
    
    XDrawLine(display, d, gcBlack, x+1, y+3, x+1, y+6);
    XDrawLine(display, d, gcLight, x,   y+3, x,   y+8);
    XDrawLine(display, d, gcLight, x,   y+8, x+8, y);
    XDrawLine(display, d, gcBlack, x,   y+9, x+8, y+1);
    XDrawLine(display, d, gcDark,  x+1, y+9, x+8, y+2);

    Tk_FreeGC(Tk_Display(tkwin), gcBlack);
}

/*
 * Element specifications
 */

/*
 *----------------------------------------------------------------------
 * +++ Indicator element implementation.
 *
 * Draws the on/off indicator for checkbuttons and radiobuttons.
 *
 * Draws a 3-D square (or diamond), raised if off, sunken if on.
 *
 */

typedef struct
{
    Tcl_Obj *backgroundObj;
    Tcl_Obj *reliefObj;
    Tcl_Obj *colorObj;
    Tcl_Obj *diameterObj;
    Tcl_Obj *marginObj;
    Tcl_Obj *borderWidthObj;
} IndicatorElement;

static Ttk_ElementOptionSpec IndicatorElementOptions[] =
{
    { "-background", TK_OPTION_BORDER,
	    Tk_Offset(IndicatorElement,backgroundObj), DEFAULT_BACKGROUND },
    { "-indicatorcolor", TK_OPTION_BORDER,
	    Tk_Offset(IndicatorElement,colorObj), DEFAULT_BACKGROUND },
    { "-indicatorrelief", TK_OPTION_RELIEF,
	    Tk_Offset(IndicatorElement,reliefObj), "raised" },
    { "-indicatordiameter", TK_OPTION_PIXELS,
	    Tk_Offset(IndicatorElement,diameterObj), "12" },
    { "-indicatormargin", TK_OPTION_STRING,
	    Tk_Offset(IndicatorElement,marginObj), "0 2 4 2" },
    { "-borderwidth", TK_OPTION_PIXELS,
	Tk_Offset(IndicatorElement,borderWidthObj), DEFAULT_BORDERWIDTH },
    {NULL}
};

/*
 * Checkbutton indicators: 3-D square with tick
 */

static void
CheckIndicatorElementGeometry(
    void *clientData, void *elementRecord,
    Tk_Window tkwin, int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    IndicatorElement *indicator = elementRecord;
    int diameter = 0;
    Ttk_GetPaddingFromObj(NULL, tkwin, indicator->marginObj, paddingPtr);
    Tk_GetPixelsFromObj(NULL, tkwin, indicator->diameterObj, &diameter);
    *widthPtr = *heightPtr = diameter + 2;
}

static void
CheckIndicatorElementDraw(
    void *clientData, void *elementRecord,
    Tk_Window tkwin, Drawable d,
    Ttk_Box b, unsigned int state)
{
    IndicatorElement *indicator = elementRecord;
    Tk_3DBorder border = 0, interior = 0;
    int relief = TK_RELIEF_RAISED;
    int borderWidth = 2;
    int diameter;
    Ttk_Padding margin;

    interior = Tk_Get3DBorderFromObj(tkwin, indicator->colorObj);
    border = Tk_Get3DBorderFromObj(tkwin, indicator->backgroundObj);
    Tcl_GetIntFromObj(NULL, indicator->borderWidthObj, &borderWidth);
    Ttk_GetPaddingFromObj(NULL,tkwin,indicator->marginObj,&margin);
    Tk_GetReliefFromObj(NULL, indicator->reliefObj, &relief);

    b = Ttk_PadBox(b, margin);

    diameter = b.width < b.height ? b.width : b.height;
    Tk_Fill3DRectangle(tkwin, d, interior, b.x, b.y, 
		       diameter, diameter, borderWidth, relief);
    
    if (state & TTK_STATE_SELECTED)
	DrawCheckMark(tkwin, d, b.x + borderWidth, b.y + borderWidth, border);
}

/*
 * Radiobutton indicators:  filled sunken circle.
 */

static void
RadioIndicatorElementGeometry(void *clientData, void *elementRecord,
			      Tk_Window tkwin, int *widthPtr, int *heightPtr,
			      Ttk_Padding *paddingPtr)
{
    IndicatorElement *indicator = elementRecord;
    int diameter = 0;
    Ttk_GetPaddingFromObj(NULL, tkwin, indicator->marginObj, paddingPtr);
    Tk_GetPixelsFromObj(NULL, tkwin, indicator->diameterObj, &diameter);
    *widthPtr = *heightPtr = diameter;
}

static void
RadioIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned int state)
{
    IndicatorElement *indicator = elementRecord;
    Display *display = Tk_Display(tkwin);
    Tk_3DBorder border = 0, interior = 0;
    int borderWidth = 2;
    unsigned int diameter, radius;
    Ttk_Padding margin;
    
    interior = Tk_Get3DBorderFromObj(tkwin, indicator->colorObj);
    border = Tk_Get3DBorderFromObj(tkwin, indicator->backgroundObj);
    Tcl_GetIntFromObj(NULL,indicator->borderWidthObj,&borderWidth);
    Ttk_GetPaddingFromObj(NULL,tkwin,indicator->marginObj,&margin);

    b = Ttk_PadBox(b, margin);

    /*
     * Draw
     */

    diameter = b.width < b.height ? b.width : b.height;
    radius = diameter / 2;
#ifdef PAT_EXPERIMENTAL    
    Draw3DCircle(tkwin, d, x, y, diameter, border);
#else
    {
	GC gcA, gcB;
	unsigned int r = radius;
	gcA = Tk_3DBorderGC(tkwin, border, TK_3D_LIGHT_GC);
	gcB = Tk_3DBorderGC(tkwin, border, TK_3D_DARK_GC);
	
	XSetLineAttributes(display, gcB, 1, LineSolid, CapRound, JoinRound );
	XDrawArc(display, d, gcB, b.x, b.y, diameter, diameter, 0, 360*64);

	XSetLineAttributes(display, gcA, 1, LineSolid, CapRound, JoinRound );
	XDrawArc(display, d, gcA, b.x+1, b.y+1, 2*r-2, 2*r-2, 30*64, 210*64);
	XDrawArc(display, d, gcA, b.x-1, b.y-1, 2*r+2, 2*r+2, 230*64, 170*64);
    }
#endif /* PAT_EXPERIMENTAL */

    /* draw the center spot */
    if (state & TTK_STATE_SELECTED) {
	GC gcBlack = GetBlackGC(tkwin);

	/*
	 * Draw this dot in two parts to avoid a sliced off edge under win32
	 */
	radius -= borderWidth;
	radius /= 2;
	b.x += borderWidth, b.y += borderWidth;
	b.x += radius, b.y += radius;
	XFillArc(display, d, gcBlack, b.x,b.y, radius*2,radius*2, 1, 12672);
	XFillArc(display, d, gcBlack, b.x,b.y, radius*2,radius*2, 12672, 23040);
        Tk_FreeGC(Tk_Display(tkwin), gcBlack);
    }
}

static Ttk_ElementSpec CheckbuttonIndicatorElementSpec =
{
    TK_STYLE_VERSION_2,
    sizeof(IndicatorElement),
    IndicatorElementOptions,
    CheckIndicatorElementGeometry,
    CheckIndicatorElementDraw
};

static Ttk_ElementSpec RadiobuttonIndicatorElementSpec =
{
    TK_STYLE_VERSION_2,
    sizeof(IndicatorElement),
    IndicatorElementOptions,
    RadioIndicatorElementGeometry,
    RadioIndicatorElementDraw
};

/*
 *----------------------------------------------------------------------
 * +++ Thumb element.
 *
 */

#define MIN_THUMB_SIZE 8

typedef struct
{
    Tcl_Obj *orientObj;
    Tcl_Obj *sizeObj;
    Tcl_Obj *borderObj;
    Tcl_Obj *reliefObj;
} ThumbElement;

static Ttk_ElementOptionSpec ThumbElementOptions[] =
{
    { "-orient", TK_OPTION_ANY,Tk_Offset(ThumbElement,orientObj),"horizontal"},
    { "-width", TK_OPTION_PIXELS, Tk_Offset(ThumbElement,sizeObj), "8" },
    { "-background", TK_OPTION_BORDER,
	    Tk_Offset(ThumbElement,borderObj), DEFAULT_BACKGROUND },
    { "-relief", TK_OPTION_RELIEF, Tk_Offset(ThumbElement,reliefObj), "raised"},
    { NULL }
};

static void
ThumbElementGeometry(
    void *clientData, void *elementRecord,
    Tk_Window tkwin, int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    ThumbElement *thumb = elementRecord;
    int orient, size;
    Tk_GetPixelsFromObj(NULL, tkwin, thumb->sizeObj, &size);
    Ttk_GetOrientFromObj(NULL, thumb->orientObj, &orient);

    if (orient == TTK_ORIENT_VERTICAL) {
	*widthPtr = size;
	*heightPtr = MIN_THUMB_SIZE;
    } else {
	*widthPtr = MIN_THUMB_SIZE;
	*heightPtr = size;
    }
}

static void
ThumbElementDraw(
    void *clientData, void *elementRecord,
    Tk_Window tkwin, Drawable d,
    Ttk_Box b, unsigned int state)
{
    ThumbElement *thumb = elementRecord;
    Tk_3DBorder border = NULL;
    int borderWidth = 2;

    border = Tk_Get3DBorderFromObj(tkwin, thumb->borderObj);

    Tk_Fill3DRectangle(tkwin, d, border, b.x, b.y, b.width, b.height, 
                       borderWidth, TK_RELIEF_RAISED);

    b.x += (b.width/2) - borderWidth;
    b.y += (b.height/2) - borderWidth;
    Tk_Fill3DRectangle(tkwin, d, border, b.x, b.y, 
        borderWidth*2, borderWidth * 2, borderWidth, TK_RELIEF_SUNKEN);
}

static Ttk_ElementSpec ThumbElementSpec =
{
    TK_STYLE_VERSION_2,
    sizeof(ThumbElement),
    ThumbElementOptions,
    ThumbElementGeometry,
    ThumbElementDraw
};

/*------------------------------------------------------------------------
 * +++ Progress bar element.
 *	Now with stripes!
 */

#if 0
/* @@@ Possibly: split "stripes" out into its own element, and use 
 * @@@ something like the following instead:
 */
TTK_BEGIN_LAYOUT(VerticalProgressbarLayout)
    TTK_GROUP("Vertical.Progressbar.trough", TTK_FILL_BOTH,
	TTK_GROUP("Vertical.Progressbar.pbar", TTK_PACK_BOTTOM,
	    TTK_NODE("Vertical.Progressbar.stripes", TTK_EXPAND)))
TTK_END_LAYOUT
TTK_BEGIN_LAYOUT(HorizontalProgressbarLayout)
    TTK_GROUP("Horizontal.Progressbar.trough", TTK_FILL_BOTH,
	TTK_GROUP("Horizontal.Progressbar.pbar", TTK_PACK_LEFT,
	    TTK_NODE("Horizontal.Progressbar.stripes", TTK_EXPAND)))
TTK_END_LAYOUT
#endif

#define DEFAULT_PBAR_THICKNESS "12"
#define DEFAULT_PBAR_LENGTH "24"
#define DEFAULT_PBAR_STRIPE "6"

typedef struct
{
    Tcl_Obj *orientObj; 	/* widget orientation */
    Tcl_Obj *thicknessObj;	/* the height/width of the bar */
    Tcl_Obj *lengthObj;		/* default width/height of the bar */
    Tcl_Obj *reliefObj; 	/* border relief for this object */
    Tcl_Obj *borderWidthObj; 	/* thickness of the border */
    Tcl_Obj *borderObj; 	/* background color */
    Tcl_Obj *stripeColorObj; 	/* color for stripes */
    Tcl_Obj *stripeThicknessObj; /* stripe thickness */
    Tcl_Obj *phaseObj;		/* animation phase */
} PbarElement;

static Ttk_ElementOptionSpec PbarElementOptions[] =
{
    { "-orient", TK_OPTION_ANY, Tk_Offset(PbarElement,orientObj),
	"horizontal" },
    { "-thickness", TK_OPTION_PIXELS, Tk_Offset(PbarElement,thicknessObj),
	DEFAULT_PBAR_THICKNESS },
    { "-barsize", TK_OPTION_PIXELS, Tk_Offset(PbarElement,lengthObj),
	DEFAULT_PBAR_LENGTH },
    { "-pbarrelief", TK_OPTION_RELIEF, Tk_Offset(PbarElement,reliefObj),
	"raised" },
    { "-borderwidth", TK_OPTION_PIXELS, Tk_Offset(PbarElement,borderWidthObj),
	DEFAULT_BORDERWIDTH },
    { "-background", TK_OPTION_BORDER, Tk_Offset(PbarElement,borderObj),
	DEFAULT_BACKGROUND },
    { "-stripecolor", TK_OPTION_COLOR, Tk_Offset(PbarElement,stripeColorObj),
	DEFAULT_FOREGROUND },
    { "-stripethickness", TK_OPTION_INT, 
	Tk_Offset(PbarElement,stripeThicknessObj), DEFAULT_PBAR_STRIPE },
    { "-phase", TK_OPTION_INT, Tk_Offset(PbarElement,phaseObj), 
	"0" },
    { NULL }
};

static void PbarElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    PbarElement *pbar = elementRecord;
    int orient, thickness, length, borderWidth;

    Ttk_GetOrientFromObj(NULL, pbar->orientObj, &orient);
    Tk_GetPixelsFromObj(NULL, tkwin, pbar->thicknessObj, &thickness);
    Tk_GetPixelsFromObj(NULL, tkwin, pbar->lengthObj, &length);
    Tk_GetPixelsFromObj(NULL, tkwin, pbar->borderWidthObj, &borderWidth);

    switch (orient) {
	case TTK_ORIENT_HORIZONTAL:
	    *widthPtr	= length;
	    *heightPtr	= thickness;
	    break;
	case TTK_ORIENT_VERTICAL:
	    *widthPtr	= thickness;
	    *heightPtr	= length;
	    break;
    }

    *paddingPtr = Ttk_UniformPadding((short)borderWidth);
}

static void PbarElementDrawStripes(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, Ttk_State state)
{
    PbarElement *pbar = elementRecord;
    Display *display = Tk_Display(tkwin);
    XColor *stripeColor = Tk_GetColorFromObj(tkwin, pbar->stripeColorObj);
    GC stripeGC = Tk_GCForColor(stripeColor, d);
    int phase = 0, stripeThickness = 6, st;
    int orient = TTK_ORIENT_HORIZONTAL;
    int i;

    Tcl_GetIntFromObj(NULL, pbar->phaseObj, &phase);
    Tcl_GetIntFromObj(NULL, pbar->stripeThicknessObj, &stripeThickness);
    Ttk_GetOrientFromObj(NULL, pbar->orientObj, &orient);

    switch (orient) {
    case TTK_ORIENT_HORIZONTAL:
	st = 2 * stripeThickness;
	for (i=0; i < b.width - 1; ++i) {
	    int x0 = b.x + i, y0 = b.y;
	    int dx = b.height - 1;
	    int on = ((st + (x0 % st) - (phase % st)) / stripeThickness) % 2;

	    if (!on) continue;
	    if (x0 + dx >= b.x + b.width)
		dx = b.x + b.width - 1 - x0;

	    XDrawLine(display, d, stripeGC, x0,y0, x0 + dx,y0 + dx);
	}
	break;
    case TTK_ORIENT_VERTICAL:
	for (i=0; i <= b.height - 1; ++i) {
	    int x0 = b.x, y0 = b.y + b.height - i;
	    int dy = b.width - 1;
	    int on = ((y0 + phase) / stripeThickness) % 2;

	    if (!on) continue;
	    if (y0 - dy < b.y)
	    	dy = y0 - b.y;

	    XDrawLine(display, d, stripeGC, x0,y0, x0 + dy,y0 - dy);
	}
    }
}

static void PbarElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, Ttk_State state)
{
    PbarElement *pbar = elementRecord;
    Tk_3DBorder border = Tk_Get3DBorderFromObj(tkwin, pbar->borderObj);
    int relief, borderWidth;

    Tk_GetPixelsFromObj(NULL, tkwin, pbar->borderWidthObj, &borderWidth);
    Tk_GetReliefFromObj(NULL, pbar->reliefObj, &relief);

    Tk_Fill3DRectangle(tkwin, d, border,
	b.x, b.y, b.width, b.height,
	borderWidth, relief);

    b = Ttk_PadBox(b, Ttk_UniformPadding((short)borderWidth));
    PbarElementDrawStripes(clientData, elementRecord, tkwin, d, b, state);
}

static Ttk_ElementSpec PbarElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(PbarElement),
    PbarElementOptions,
    PbarElementGeometry,
    PbarElementDraw
};


/* ----------------------------------------------------------------------
 *
 * Widget specifications
 *
 * ----------------------------------------------------------------------
 */

TTK_BEGIN_LAYOUT(VerticalStepScrollbarLayout)
    TTK_GROUP("Vertical.Scrollbar.trough", TTK_FILL_BOTH,
	TTK_NODE("Vertical.Scrollbar.uparrow", TTK_PACK_TOP|TTK_FILL_X)
	TTK_NODE("Vertical.Scrollbar.downarrow", TTK_PACK_BOTTOM|TTK_FILL_X)
	TTK_NODE("Vertical.Scrollbar.uparrow", TTK_PACK_BOTTOM|TTK_FILL_X)
	TTK_NODE("Vertical.Scrollbar.thumb", TTK_PACK_TOP|TTK_EXPAND|TTK_FILL_BOTH)   )
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(HorizontalStepScrollbarLayout)
    TTK_GROUP("Horizontal.Scrollbar.trough", TTK_FILL_BOTH,
	TTK_NODE("Horizontal.Scrollbar.leftarrow", TTK_PACK_LEFT|TTK_FILL_Y)
	TTK_NODE("Horizontal.Scrollbar.rightarrow", TTK_PACK_RIGHT|TTK_FILL_Y)
	TTK_NODE("Horizontal.Scrollbar.leftarrow", TTK_PACK_RIGHT|TTK_FILL_Y)
	TTK_NODE("Horizontal.Scrollbar.thumb", TTK_PACK_LEFT|TTK_EXPAND|TTK_FILL_BOTH) )
TTK_END_LAYOUT


int DLLEXPORT
StepTheme_Init(Tcl_Interp *interp)
{
    Ttk_Theme theme, parentPtr;

    /*
     * Create the new style engine.
     */
    parentPtr = Ttk_GetTheme(interp, "alt");
    theme = Ttk_CreateTheme(interp, "step", parentPtr);

    if (!theme)
        return TCL_ERROR;

    /*
     * Register any new elements required for this style engine.
     */

    Ttk_RegisterElement(interp, theme, "Checkbutton.indicator",
			    &CheckbuttonIndicatorElementSpec, NULL);
    Ttk_RegisterElement(interp, theme, "Radiobutton.indicator",
			    &RadiobuttonIndicatorElementSpec, NULL);

    Ttk_RegisterElement(interp, theme, "thumb", &ThumbElementSpec, NULL);
    Ttk_RegisterElement(interp, theme, "pbar", &PbarElementSpec, NULL);

    /*
     * Register any new widget layouts.
     */

    Ttk_RegisterLayout(theme, "Vertical.TScrollbar",
                       VerticalStepScrollbarLayout);
    Ttk_RegisterLayout(theme, "Horizontal.TScrollbar",
                       HorizontalStepScrollbarLayout);

    Tcl_PkgProvide(interp, "tile::theme::step", "0.0.2");

    return TCL_OK;
}

/*EOF*/
