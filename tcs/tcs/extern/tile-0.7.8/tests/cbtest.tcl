##
# combobox test program:
#
# side-by-side-by-side comparison of Tile, BWidget, and Brian Oakley's combobox
#

#
# Autocomplete: maybe need custom match procedure? (string match -nocase)
#
# Things to check:
# 	Focus indicator
#	Blinking insert cursor (none on readonly combobox)
#	Listbox scrollbar arrow lines up with popdown arrow
#	Mouse cursor (I-beam vs. normal) over various elements.
#	Normal mouse cursor in readonly combobox
#	Location of popdown menu when close to screen edge
#	Focus returns to combobox on Unpost (Cancel and Select)
#	ButtonRelease outside of popdown - Cancel? Select? Leave posted?
#	Keyboard traversal (incl. Shift+Tab).
#	-state disabled: 
#	+ grayed out
#	+ do not take focus on click
#	+ do not post listbox
#	Click in editable combobox -- should set icursor, don't select
#	Keyboard traversal into combobox -- should select
#	Traversal out of combobox (both <Tab> and <Shift-Tab>) 
#	Change value (using other combobox) -- repost listbox --
#	  make sure proper entry is highlighted.
#

lappend auto_path . ; package require tile
package require BWidget
package require combobox

source [file join [file dirname [info script]] testutils.tcl]

set values \
    [list abc def ghi jkl mno pqrs tuv wxyz yabba dabba scooby doobie doo]

grid	[ttk::label .l1 -text "Tile"] \
	[ttk::label .l2 -text "BWidget"] \
	[ttk::label .l3 -text "Oakley"] \
	-sticky news;

ttk::combobox .rcb1 -width 30 -textvariable V -values $values -state readonly
ComboBox .rcb2 -width 30 -textvariable V -values $values -editable false
combobox::combobox .rcb3 -textvariable V -width 30 -listvar values -editable false

ttk::combobox .ecb1 -width 30 -textvariable V -values $values
ComboBox .ecb2 -width 30 -textvariable V -values $values -editable true ;#-autocomplete true
combobox::combobox .ecb3 -textvariable V -width 30 -listvar values -editable true

grid .rcb1 .rcb2 .rcb3 -sticky news -pady 4 -padx 4 -row 2
grid .ecb1 .ecb2 .ecb3 -sticky news -pady 4 -padx 4 -row 3
grid columnconfigure . 0 -uniform c -weight 1
grid columnconfigure . 1 -uniform c -weight 1

# Active element monitor:
#
ttk::label .e -textvariable ::element
bind .rcb1 <Motion> { set ::element [%W identify %x %y] }
bind .ecb1 <Motion> { set ::element [%W identify %x %y] }

# Focus monitor:
#
ttk::label .f -textvariable ::focusWidget
proc focusMonitor {} { set ::focusWidget [focus] ; after 200 focusMonitor }
focusMonitor

# Grab monitor:
#
ttk::label .g -textvariable ::grabWidget
proc grabMonitor {} {
    global grabWidget
    set grabWidget [grab current]
    if {$grabWidget ne ""} {
	lappend grabWidget [grab status $grabWidget]
    }
    after 200 grabMonitor
}
grabMonitor
grid .e .f .g -row 1 -sticky news

###

focus .ecb1

bind all <Alt-Key-d> { %W configure -state disabled }	;# "&disable"
bind all <Alt-Key-e> { %W configure -state normal }	;# "&enable"
bind all <Alt-Key-w> { %W configure -state readonly }	;# "&write-protect"

bind all <Alt-Key-q> { destroy . }
bind all <Alt-Key-b> { error "BGerror - testing" }

bind all <Control-ButtonPress-1> { focus -force %W }

# In case of a stuck grab: <Control-Button-1> to set focus; <Alt-q> to quit
