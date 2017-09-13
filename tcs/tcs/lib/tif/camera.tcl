namespace eval tif {

   snit::widget camera {

   # The only component is a canvas to draw the blob on.
      component canvas

   # Variables that control the drawing.
      variable xc 102
      variable yc 102

   # Current number of stars.
      variable nstars 0

   # Picture scale
      option -scale 4.0

   # Suffix for variables containing the data.
      option -mount mount
      option -guider guider

   # All other options are passed to the canvas.
      delegate option * to canvas except {-borderwidth -bd}

   # Type constructor to set the default size and border width.
      typeconstructor {
         option add *Camera.width 401
         option add *Camera.height 401
         option add *Camera.background grey40 2
      }

   # Constructor
      constructor {args} {

      # Create and install the canvas.
         install canvas using canvas $win.canvas
         grid $canvas -sticky nsew

      # Make the canvas expand with the hull.
         grid rowconfigure $win 0 -weight 1
         grid columnconfigure $win 0 -weight 1

      # Create guider pickoff mirror
         $canvas create rectangle 0 0 0 0 -tags guider -fill black

      # Create the arrow that points north
         $canvas create line 10 20 10 5 -arrow last -fill white -tags north

      # Bind resize events to the redraw method.
         bind $canvas <Configure> [mymethod resize %w %h]

      # Configure.
         $self configurelist $args
      }

      method reposition {} {
         set i 0
         set s $options(-scale)

         set x $tpk::xguider($options(-guider))
         set y $tpk::yguider($options(-guider))
         set n [llength $tpk::sample($options(-mount))]
         set n [expr { $n / 2 }]

      # Move the guider.
         $canvas coords guider \
               [expr { round($x) * $s + $xc - 8 }] \
               [expr { round($y) * $s + $yc - 8 }] \
               [expr { round($x) * $s + $xc + 8 }] \
               [expr { round($y) * $s + $yc + 8 }]
               
     # If the number of star has changed re-create them.
         if { $nstars != $n } {
            for { set i 0 } { $i < $nstars } { incr i } {
               $canvas delete star$i
            }
            set nstars $n
            for { set i 0 } { $i < $nstars } { incr i } {
               set colour grey[expr \
                     { 99 - int( double($i) / double($nstars) * 50.0) }]
               $canvas create oval 0 0 0 0 -tags star$i -fill $colour \
                     -outline ""
            }
         }

      # Position the stars.
         set i 0
         foreach {x y} $tpk::sample($options(-mount)) {
            $canvas coords star$i \
                  [expr { round($x) * $s + $xc - 3 }] \
                  [expr { round($y) * $s + $yc - 3 }] \
                  [expr { round($x) * $s + $xc + 3 }] \
                  [expr { round($y) * $s + $yc + 3 }]
            incr i
         }

      # Redraw the compass arrow.
         $canvas coords north \
               [expr { 20.0 - sin(-$tpk::field_orient($options(-mount))) * 10.0 }] \
               [expr { 20.0 - cos(-$tpk::field_orient($options(-mount))) * 10.0 }] \
               [expr { 20.0 + sin(-$tpk::field_orient($options(-mount))) * 10.0 }] \
               [expr { 20.0 + cos(-$tpk::field_orient($options(-mount))) * 10.0 }]
      }

   # resize method.
      method resize {w h} {

         set s $options(-scale)
         set xc [expr { $w / 2.0 }]
         set yc [expr { $h / 2.0 }]
         $canvas delete grid
         for { set i -50 } { $i < 50 } { incr i 10} {
            set x [expr {$xc + $i * $s}]
            set y [expr {$yc + $i * $s}]
            $canvas create line 0 $y $w $y -fill grey50 -tags grid
            $canvas create line $x 0 $x $h -fill grey50 -tags grid
         }
         $canvas create line 0 $yc $w $yc -fill grey70 -tags grid
         $canvas create line $xc 0 $xc $h -fill grey70 -tags grid
         $canvas lower grid
      }
   }
}
