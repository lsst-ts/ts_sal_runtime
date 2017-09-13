# blue.tcl - Copyright (C) 2004 Pat Thoyts <patthoyts@users.sourceforge.net>
#
# blue.tcl,v 1.31 2006/08/04 12:05:43 patthoyts Exp
#
#

namespace eval tile::theme::blue {

    package provide tile::theme::blue 0.8

    variable I
    array set I [tile::LoadImages \
                     [file join [file dirname [info script]] blue] *.gif]
    
    variable colors
    array set colors {
	-frame  	"#6699cc"
	-lighter	"#bcd2e8"
	-window	 	"#e6f3ff"
	-selectbg	"#ffff33"
	-selectfg	"#000000"
	-disabledfg	"#666666"
    }

    style theme create blue -settings {

	style configure . \
	    -borderwidth 	1 \
	    -background 	$colors(-frame) \
	    -fieldbackground	$colors(-window) \
	    -troughcolor	$colors(-lighter) \
	    -selectbackground	$colors(-selectbg) \
	    -selectforeground	$colors(-selectfg) \
	    ;
	style map . -foreground [list disabled $colors(-disabledfg)]

	## Buttons.
	#
	style configure TButton -padding "10 0"
	style layout TButton {
	    Button.button -children {
		Button.focus -children {
		    Button.padding -children {
			Button.label
		    }
		}
	    }
	}

	style element create button image $I(button-n) \
	    -map [list pressed $I(button-p)  active $I(button-h)] \
	    -border 4 -sticky ew

	style element create Checkbutton.indicator image $I(check-nu) \
	    -width 24 -sticky w -map [list \
		{!disabled active selected} $I(check-hc) \
		{!disabled active} $I(check-hu) \
		{!disabled selected} $I(check-nc) ]

	style element create Radiobutton.indicator image $I(radio-nu) \
	    -width 24 -sticky w -map [list \
		{!disabled active selected} $I(radio-hc) \
		{!disabled active} $I(radio-hu) \
		selected $I(radio-nc) ]

	style configure TMenubutton -relief raised -padding {10 2}
	style configure TRadiobutton -padding 1
	style configure TCheckbutton -padding 1

	## Toolbar buttons.
	#
	style configure Toolbutton \
	    -width 0 -relief flat -borderwidth 2 -padding 4 \
	    -background $colors(-frame) -foreground #000000 ;
	style map Toolbutton -background [list active $colors(-selectbg)] 
	style map Toolbutton -foreground [list active $colors(-selectfg)] 
	style map Toolbutton -relief {
	    disabled 	flat
	    selected	sunken  
	    pressed 	sunken  
	    active  	raised
	}

	## Entry widgets.
	#
	style configure TEntry \
	    -selectborderwidth 1 -padding 2 -insertwidth 2 -font TkTextFont
	style configure TCombobox \
	    -selectborderwidth 1 -padding 2 -insertwidth 2 -font TkTextFont

	## Notebooks.
	#
        style element create tab image $I(tab-n) -border {2 2 2 0} \
            -map [list selected $I(tab-h) active $I(tab-h)]
        style configure TNotebook -padding 2 -tabmargins {2 2 2 0}
        style map TNotebook.Tab -expand [list active {2 0 2 0} selected {2 0 2 0}]

	## Labelframes.
	#
	style configure TLabelframe -borderwidth 2 -relief groove

	## Scrollbars.
	#
	style layout Vertical.TScrollbar {
	    Scrollbar.trough -children {
		Scrollbar.uparrow -side top
		Scrollbar.downarrow -side bottom
		Scrollbar.uparrow -side bottom
		Vertical.Scrollbar.thumb -side top -expand true -sticky ns
	    }
	}

	style layout Horizontal.TScrollbar {
	    Scrollbar.trough -children {
		Scrollbar.leftarrow -side left
		Scrollbar.rightarrow -side right
		Scrollbar.leftarrow -side right
		Horizontal.Scrollbar.thumb -side left -expand true -sticky we
	    }
	}

	style element create Horizontal.Scrollbar.thumb image $I(sb-thumb) \
	    -map [list {pressed !disabled} $I(sb-thumb-p)] -border 3

	style element create Vertical.Scrollbar.thumb image $I(sb-vthumb) \
	    -map [list {pressed !disabled} $I(sb-vthumb-p)] -border 3

	foreach dir {up down left right} {
	    style element create ${dir}arrow image $I(arrow${dir}) \
		-map [list \
		    disabled $I(arrow${dir}) \
		    pressed $I(arrow${dir}-p) \
		    active $I(arrow${dir}-h)] \
	        -border 1 -sticky {}
	}

	## Scales.
	#
	style element create Scale.slider \
	    image $I(slider) -map [list {pressed !disabled} $I(slider-p)]

	style element create Vertical.Scale.slider \
	    image $I(vslider) -map [list {pressed !disabled} $I(vslider-p)]

        ## Progressbar
        #
        style element create Horizontal.Progressbar.pbar image $I(sb-thumb) \
            -map [list {pressed !disabled} $I(sb-thumb-p)] -border 2
        style element create Vertical.Progressbar.pbar image $I(sb-vthumb) \
            -map [list {pressed !disabled} $I(sb-vthumb-p)] -border 2

        ## Statusbar parts
        #
        style element create sizegrip image $I(sizegrip)

        ## Paned window parts.
        #
        style element create hsash image $I(hseparator-n) -border {2 0} \
            -map [list {active !disabled} $I(hseparator-a)]
        style element create vsash image $I(vseparator-n) -border {0 2} \
            -map [list {active !disabled} $I(vseparator-a)]
    }
}

