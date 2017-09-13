/* scroll.c,v 1.5 2006/08/27 16:01:00 jenglish Exp
 *
 * Copyright 2004, Joe English
 *
 * Support routines for scrollable widgets.
 *
 * (This is sort of half-baked; needs some work)
 *
 * Scrollable interface:
 *
 * 	+ 'first' is controlled by [xy]view widget command 
 * 	  and other scrolling commands like 'see';
 *      + 'total' depends on widget contents;
 *      + 'last' depends on first, total, and widget size.
 *
 * Choreography (typical usage):
 *
 * 	1. User adjusts scrollbar, scrollbar widget calls its -command
 * 	2. Scrollbar -command invokes the scrollee [xy]view widget method
 * 	3. ScrollviewCommand calls ScrollTo(), which updates 
 * 	   'first' and schedules a redisplay.
 * 	4. Once the scrollee knows 'total' and 'last' (typically in 
 * 	   the LayoutProc), call Scrolled(h,first,last,total) to 
 * 	   synchronize the scrollbar.
 * 	5. The scrollee -[xy]scrollcommand is called (in an idle callback)
 * 	6. Which calls the scrollbar 'set' method and redisplays the scrollbar.
 *
 * If the scrollee has internal scrolling (e.g., a 'see' method), 
 * it should ScrollTo() directly (step 2).
 *
 * If the widget value changes, it should call Scrolled() (step 4).
 * (This usually happens automatically when the widget is redisplayed).
 *
 * If the scrollee's -[xy]scrollcommand changes, it should call
 * ScrollbarUpdateRequired, which will invoke step (5) (@@@ Fix this)
 */

#include <tk.h>
#include "tkTheme.h"
#include "widget.h"

/* Private data:
 */
#define SCROLL_UPDATE_PENDING  (0x1)
#define SCROLL_UPDATE_REQUIRED (0x2)

struct ScrollHandleRec
{
    unsigned 	flags;
    WidgetCore	*corePtr;
    Scrollable	*scrollPtr;
};

/* CreateScrollHandle --
 * 	Initialize scroll handle.
 */
ScrollHandle CreateScrollHandle(WidgetCore *corePtr, Scrollable *scrollPtr)
{
    ScrollHandle h = (ScrollHandle)ckalloc(sizeof(*h));

    h->flags = 0;
    h->corePtr = corePtr;
    h->scrollPtr = scrollPtr;

    scrollPtr->first = 0;
    scrollPtr->last = 1;
    scrollPtr->total = 1;
    return h;
}

void FreeScrollHandle(ScrollHandle h)
{
    Tcl_EventuallyFree((ClientData)h, TCL_DYNAMIC);
}

/* UpdateScrollbar --
 *	Call the -scrollcommand callback to sync the scrollbar.
 * 	Returns: Whatever the -scrollcommand does.
 */
static int UpdateScrollbar(Tcl_Interp *interp, ScrollHandle h)
{
    Scrollable *s = h->scrollPtr;
    char args[TCL_DOUBLE_SPACE * 2];
    int code;

    h->flags &= ~(SCROLL_UPDATE_PENDING | SCROLL_UPDATE_REQUIRED);

    if (s->scrollCmd == NULL)
	return TCL_OK;

    sprintf(args, " %g %g",
		(double)s->first / s->total,
		(double)s->last / s->total);

    Tcl_Preserve(h->corePtr);
    code = Tcl_VarEval(interp, s->scrollCmd, args, NULL);
    if (WidgetDestroyed(h->corePtr)) {
	Tcl_Release(h->corePtr);
	return TCL_ERROR;
    }
    Tcl_Release(h->corePtr);

    if (code != TCL_OK) {
	/* Disable the -scrollcommand, add to stack trace:
	 */
	ckfree(s->scrollCmd);
	s->scrollCmd = 0;

	Tcl_AddErrorInfo(interp, /* @@@ "horizontal" / "vertical" */
		"\n    (scrolling command executed by ");
	Tcl_AddErrorInfo(interp, Tk_PathName(h->corePtr->tkwin));
	Tcl_AddErrorInfo(interp, ")");
    }
    return code;
}

/* UpdateScrollbarBG --
 * 	Idle handler to update the scrollbar.
 */
static void UpdateScrollbarBG(ClientData clientData)
{
    ScrollHandle h = (ScrollHandle)clientData;
    Tcl_Interp *interp = h->corePtr->interp;
    int code;

    if (WidgetDestroyed(h->corePtr)) {
	Tcl_Release(clientData);
	return;
    }

    Tcl_Preserve((ClientData) interp);
    code = UpdateScrollbar(interp, h);
    if (code == TCL_ERROR && !Tcl_InterpDeleted(interp)) {
	Tcl_BackgroundError(interp);
    }
    Tcl_Release((ClientData) interp);
    Tcl_Release(clientData);
}

/* Scrolled --
 * 	Update scroll info, schedule scrollbar update.
 */
void Scrolled(ScrollHandle h, int first, int last, int total)
{
    Scrollable *s = h->scrollPtr;
    
    /* Sanity-check inputs:
     */
    if (total <= 0) {
	first = 0;
	last = 1;
	total = 1;
    }

    if (s->first != first || s->last != last || s->total != total
	    || (h->flags & SCROLL_UPDATE_REQUIRED))
    {
	s->first = first;
	s->last = last;
	s->total = total;

	if (!(h->flags & SCROLL_UPDATE_PENDING)) {
	    Tcl_Preserve((ClientData)h);
	    Tcl_DoWhenIdle(UpdateScrollbarBG, (ClientData)h);
	    h->flags |= SCROLL_UPDATE_PENDING;
	}
    }
}

/* ScrollbarUpdateRequired --
 * 	Force a scrollbar update at the next call to Scrolled(),
 * 	even if scroll parameters haven't changed (e.g., if
 * 	-yscrollcommand has changed).
 */

void ScrollbarUpdateRequired(ScrollHandle h)
{
    h->flags |= SCROLL_UPDATE_REQUIRED;
}

/* ScrollviewCommand --
 * 	Widget [xy]view command implementation.
 *
 *  $w [xy]view -- return current view region
 *  $w [xy]view $index -- set topmost item
 *  $w [xy]view moveto $fraction
 *  $w [xy]view scroll $number $what -- scrollbar interface
 */
int ScrollviewCommand(
    Tcl_Interp *interp, int objc, Tcl_Obj *const objv[], ScrollHandle h)
{
    Scrollable *s = h->scrollPtr;
    int newFirst = s->first;

    if (objc == 2) {
	char buf[TCL_DOUBLE_SPACE * 2];
	sprintf(buf, "%g %g",
		(double)s->first / s->total,
		(double)s->last / s->total);
	Tcl_SetResult(interp, buf, TCL_VOLATILE);
	return TCL_OK;
    } else if (objc == 3) {
	if (Tcl_GetIntFromObj(interp, objv[2], &newFirst) != TCL_OK) {
	    return TCL_ERROR;
	}
    } else {
	double fraction;
	int count;

	switch (Tk_GetScrollInfoObj(interp, objc, objv, &fraction, &count)) {
	    case TK_SCROLL_ERROR:
		return TCL_ERROR;
	    case TK_SCROLL_MOVETO:
		newFirst = (int) ((fraction * s->total) + 0.5);
		break;
	    case TK_SCROLL_UNITS:
		newFirst = s->first + count;
		break;
	    case TK_SCROLL_PAGES: {
		int perPage = s->last - s->first;	/* @@@ */
		newFirst = s->first + count * perPage;
		break;
	    }
	}
    }

    ScrollTo(h, newFirst);

    return TCL_OK;
}

void ScrollTo(ScrollHandle h, int newFirst)
{
    Scrollable *s = h->scrollPtr;

    if (newFirst >= s->total)
	newFirst = s->total - 1;
    if (newFirst > s->first && s->last >= s->total) /* don't scroll past end */
	newFirst = s->first;
    if (newFirst < 0)
	newFirst = 0;

    if (newFirst != s->first) {
	s->first = newFirst;
	TtkRedisplayWidget(h->corePtr);
    }
}
