namespace eval tif {

# A status widget is a coloured blob that changes colour to indicate the
# the status of something. The status can be "ok", "warn" or "error" and
# the colours assigned to these status is by default green, yellow and 
# red respecively.
   snit::widget status {

   # The only component is a canvas to draw the blob on.
      component canvas

   # The state is set with the -status option.
      option -status -configuremethod newstatus -validatemethod checkstatus \
            -default ok

   # Colours associated with the states.
      option {-okcolour okColour OkColour} -configuremethod newstatus
      option {-warncolour warnColour WarnColour} -configuremethod newstatus
      option {-errorcolour errorColour ErrorColour} -configuremethod newstatus
   
   # Borderwidth option has to be intercepted as the picture needs to be
   # re-drawn if the border is changed.
      option {-borderwidth borderWidth BorderWidth} -configuremethod newborder

   # All other options are passed to the canvas.
      delegate option * to canvas

   # Type constructor to set the default size and border width.
      typeconstructor {
         option add *Status.width 20
         option add *Status.height 20
         option add *Status.borderWidth 2
         option add *Status.okColour green
         option add *Status.warnColour yellow
         option add *Status.errorColour red
      }

   # Constructor
      constructor {args} {

      # Create and install the canvas.
         install canvas using canvas $win.canvas
         grid $canvas -sticky nsew

      # Create the blob.
         $canvas create oval 0 0 0 0 -tags blob -outline ""

      # Make the canvas expand with the hull.
         grid rowconfigure $win 0 -weight 1
         grid columnconfigure $win 0 -weight 1

      # Bind resize events to the redraw method.
         bind $canvas <Configure> [mymethod resize %w %h]

      # Configure.
         $self configurelist $args

      # Set the colour of the blob.
         $canvas itemconfigure blob -fill $options(-$options(-status)colour)
      }

   # resize method.
      method resize {w h} {

         set b [$canvas cget -borderwidth]
         $canvas coords blob [expr {$b + 3}] [expr {$b + 3}] \
               [expr {$w - $b - 3}] [expr {$h - $b - 3}]
      }

   # Validate method for status.
      method checkstatus {option value} {
         if {[lsearch -exact [list ok warn error] $value] < 0 } {
            error "-status must be one of ok, warn or error"
         }
      }

   # Configure method for options that change the colour of the blob.
      method newstatus {option value} {

      # Store the option.
         set options($option) $value

      # Set the colour of the blob.
         $canvas itemconfigure blob -fill $options(-$options(-status)colour)
      }

   # Configure method for change of border.
      method newborder {option value} {
   
      # Configure the canvas.
         $canvas configure $option $value

      # Store the option
         set options($option) $value

      # Synthesize a resize event.
         $self resize [winfo width $canvas] [winfo height $canvas]
      }
   }
}
