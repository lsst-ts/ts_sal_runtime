namespace eval tif {

   snit::type strip {

      variable canvas
      variable var
      option -scale 1.0
      option -zero ""
      option -color -configuremethod newcolor -default white
      variable vals ""
      variable count 0

      constructor {can v args} {
         set canvas $can
         set var $v

         uplevel #0 [list trace add variable $var write [mymethod addpoint]]
         $canvas create line 0 0 0 0 -tags $self -fill white

         $self configurelist $args
      }

      method addpoint {name1 name2 op} {

      # Maximum number of points is the width of the canvas.
         set nmax [winfo width $canvas]
         if { $count == $nmax } {
            set vals [lrange $vals 1 end]
         } else {
            incr count
         }
         lappend vals [uplevel #0 set $name1]

      # Constuct coordinate list.
         set x 0
         set z $options(-zero)
         if { $z == "" } {
            set z [expr { ([lindex $vals 0 0] + [lindex $vals end end]) / 2.0 \
                  - [winfo height $canvas] / 2.0 }]
         }
         foreach y $vals {
            lappend coords $x \
                  [expr { ($y - $z) * $options(-scale)}]
            incr x
         }

      # Update line
         if { $count > 2 } {
            $canvas coords $self $coords
         }
      }

      method newcolor {option value} {
         $canvas itemconfigure $self -fill $value
         set options($option) $value
      }

      method dump {} {
         return $vals
      }
   }
}
