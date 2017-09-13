# [20 Mar 2005] - interactive test for Tile panedwindow widget

package require tile

option add *Text.height 10
option add *Listbox.height 5
option add *Panedwindow.opaqueResize 1
option add *Panedwindow.OpaqueResize 1

ttk::paned .pw -orient vertical
#panedwindow .pw -opaqueresize true -orient vertical

#frame .pw
#proc .pw-add {win} { pack $win -side top -expand false -fill x }

.pw add [ttk::frame .pw.f1];#$ -stretch always
.pw add [ttk::frame .pw.f2];#$ -stretch always
.pw add [set w3 [listbox .pw.f3]];#$ -stretch always
.pw add [ttk::frame .pw.f4];#$ -stretch always

pack [set w1 [listbox .pw.f1.l]] -expand true -fill both
pack [set w2 [listbox .pw.f2.l]] -expand true -fill both
#X pack [set w3 [listbox .pw.f3.l]] -expand true -fill both
pack [set w4 [listbox .pw.f4.l]] -expand true -fill both

pack [label .l -textvariable ::element] -side bottom -expand false -fill x
pack .pw -expand true -fill both -side top

bind .pw <Motion> { set ::element "[%W identify %x %y] - %x,%y" }

bind . <KeyPress-Escape> [list destroy .]

foreach w [list $w1 $w2 $w3] {
    foreach string {abc def ghi jkl mno pqr stu vwx yz} {
    	$w insert end $string
    }
}
