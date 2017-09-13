namespace eval tif {

# A widget that displays a plot of the whole sky with the demand and 
# actual position of the telescope marked.
   snit::widget skyplot {

   # The only component is the canvas for the drawing.
      component canvas

   # Scale factor for picture generation.
      variable scale 1.0

   # Current size of the canvas.
      variable cwidth 0
      variable cheight 0

   # Pixel coordinates of canvas centre.
      variable cx 0
      variable cy 0

   # Demand and actual telescope position.
      option -demand -default {0 0} -configuremethod newtelpos
      option -position -default {0 0} -configuremethod newtelpos

   # Horizon limit.
      option -horizon -default 10 -configuremethod redrawoption

   # All other options are delegated to the canvas.
      delegate option * to canvas except {-borderwidth -bd}

   # Constructor
      constructor {args} {

      # Install canvas and make it expand with the hull.
         install canvas using canvas $win.canvas -width 1 -height 1
         grid $canvas -sticky ewns
         grid rowconfigure $win 0 -weight 1
         grid columnconfigure $win 0 -weight 1

      # Bind to resize events.
         bind $win <Configure> "$self resize %w %h"

      # Process options.
         $self configurelist $args
      }

   # Handles changes to options that require the picture to be redrawn.
      method redrawoption {option value} {
         set options($option) $value
         $self redraw $cwidth
      }

   # Redraws the picture in response to a change in size.
      method resize {w h} {

      # Force the picture to be square.
         if { $w != $h } {
            set s [expr { $w > $h ? $w : $h }]
            $canvas configure -width $s -height $s
         } else {

         # If the size has changed redraw the picture
            if { $w != $cwidth || $h != $cheight } {
               $self redraw $w
            }
         }
      }

   # redraws the picture.
      method redraw {s} {

      # Store new size
         set cwidth $s
         set cheight $s

      # Delete everything
         $canvas delete all

      # Calculate the coordinates of the centre.
         set cx [expr {$s / 2}]
         set cy [expr {$s / 2}]

      # calculate the plot scale from the canvas size the margin for the
      # text annotation and the elevation of the horizon.
         set margin 30
         set plotsize [expr {$s - $margin} ]
         set r [$self d2r [expr {90.0 - $options(-horizon)}]]
         set scale [expr {$plotsize / sin($r) * sqrt( 1.0 + cos($r) ) / 2.0}]

      # Create everything as if the centre of the plot was at 0,0 in
      # canvas coordinates.

      # The sky down to the horizon limit.
         set r [$self el2r $options(-horizon)]
         $canvas create oval [expr {-$r}] [expr {-$r}] \
               [expr {$r}] [expr {$r}] -fill darkblue

      #  30 degree grid in azimuth.
         foreach d {0 30 60 90 120 150} {
            set d [$self d2r $d]
            set x [expr $r * cos($d)]
            set y [expr $r * sin($d)]
            $canvas create line [expr {- $x}] [expr {- $y}] $x $y -fill black
         }

      #  20 degree grid in elevation from the pole.
         foreach d {70 50 30} {
            set r [$self el2r $d]
            $canvas create oval [expr {- $r}] [expr {- $r}] $r $r -outline black
         }

      # Move everything to the centre.
         $canvas move all $cx $cy 

      # Marker for the telescope position and demand.
         $canvas create oval -1 -1 -1 -1 -fill "" -outline orange -tags demand
         $canvas create oval -1 -1 -1 -1 -fill orange -outline "" -tags position

      # Compass point labels
         $canvas create text $cx 2 -text N -anchor n
         $canvas create text [expr {$plotsize + $margin}] $cy -text E -anchor e
         $canvas create text 2 $cy -text W -anchor w
         $canvas create text $cx [expr {$plotsize + $margin}] -text S -anchor s
      }

   # Move the telescope position indicators into position.
      method newtelpos {option value} {

      # If the position is below the horizon limit set the coordinates
      # to somewhere off the canvas.
         if { [lindex $value 1] < $options(-horizon) } {
            set x0 -1
            set y0 -1
            set x1 -1
            set y1 -1
         } else {

         # Calculate the pixel coordinate of the centre.
            set r [$self el2r [lindex $value 1]]
            set d [$self d2r [lindex $value 0]]
            set x [expr {$r * sin($d)}]
            set y [expr {- $r * cos($d)}]

         # Calculate bounding box
            set x0 [expr {$cx + $x - 5}]
            set y0 [expr {$cy + $y - 5}]
            set x1 [expr {$cx + $x + 5}]
            set y1 [expr {$cy + $y + 5}]
         }

      # Set the indicator coordinates
         switch -- $option {
            -demand {
               $canvas coords demand $x0 $y0 $x1 $y1
            }
            -position {
               $canvas coords position $x0 $y0 $x1 $y1
            }
         }
         set options($option) $value
      }

      # Convert degrees to radians
      method d2r {r} {
         return [expr {$r * 0.01745329251994}]
      }

   #  Convert an elevation in degrees to a radius in pixels.
      method el2r {el} {
         set r [$self d2r [expr {90.0 - $el}]]
         return [expr {$scale * sin($r) / sqrt( 1.0 + cos($r) )}]
      }
   }
}
