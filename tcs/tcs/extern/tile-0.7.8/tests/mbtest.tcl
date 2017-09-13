
lappend auto_path .
package require tile
style theme use alt

proc fillMenu {menu} {
    foreach dir {above below left right flush} {
	$menu add command -label [string totitle $dir] \
	    -command [list [winfo parent $menu] configure -direction $dir]
    }
    $menu add cascade -label "Submenu" -menu [set submenu [menu $menu.submenu]]
    $submenu add command -label "Subcommand 1"
    $submenu add command -label "Subcommand 2"
    $submenu add command -label "Subcommand 3"

    $menu add separator
    $menu add command -label "Quit"  -command [list destroy .]
}

tmenubutton .tmb -text "Menu" 
.tmb configure -menu [menu .tmb.menu]
fillMenu .tmb.menu

menubutton .mb -text "Menu" 
.mb configure -menu [menu .mb.menu] -takefocus 1
fillMenu .mb.menu

tk_optionMenu .om OM "Option 1" "Option 2" "Option 3" "Option 4"

namespace import -force tile::menubutton
tk_optionMenu .tom OM "Option 1" "Option 2" "Option 3" "Option 4"

grid .tmb .mb -sticky news 
grid .tom .om -sticky news 
grid columnconfigure . 0 -weight 1 -uniform w
grid columnconfigure . 1 -weight 1 -uniform w

