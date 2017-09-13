namespace eval tif {
   snit::widget mountview {
      component pos
      component tarposlabel
      component tarpos
      component telposlabel
      component telpos
      component fieldorientlabel
      component fieldorient
      component azel
      component demand
      component achieved
      component diff
      component azlabel
      component azdemand
      component azachieved
      component azdiff
      component azstatus
      component ellabel
      component eldemand
      component elachieved
      component eldiff
      component elstatus
      component rotlabel
      component rotdemand
      component rotachieved
      component rotdiff
      component rotstatus
      component tiplabel
      component tipdemand
      component tipachieved
      component tipdiff
      component tiltlabel
      component tiltdemand
      component tiltachieved
      component tiltdiff
      component gxlabel
      component gxdemand
      component gxachieved
      component gxdiff
      component gylabel
      component gydemand
      component gyachieved
      component gydiff
      component skyplot
      option -mount mount
      option -guider guider
      delegate option * to hull
      constructor {args} {

      # Build display of target and telescope positions
         install pos using frame $win.pos
         install tarposlabel using ttk::label $pos.tarlabel \
               -text "Target Position:" -anchor e
         install tarpos using ttk::label $pos.tarpos -relief sunken -width 25
         install telposlabel using ttk::label $pos.tellabel \
               -text "Telescope Position:" -anchor e
         install telpos using ttk::label $pos.telpos -relief sunken -width 25
         install fieldorientlabel using ttk::label $pos.folabel \
               -text "Field Orientation:" -anchor e
         install fieldorient using ttk::label $pos.fieldorient -relief sunken \
               -width 11
         grid $tarposlabel $tarpos -sticky ew -pady 3
         grid $telposlabel $telpos -sticky ew -pady 3
         grid $fieldorientlabel $fieldorient -sticky w -pady 3


      # Build display of Az,El and rotator position.
         install azel using frame $win.azel
         install demand using ttk::label $azel.demand -text demand
         install achieved using ttk::label $azel.achieved -text achieved
         install diff using ttk::label $azel.diff -text difference
         install azlabel using ttk::label $azel.azlabel -text Azimuth: -anchor e
         install azdemand using ttk::label $azel.azdemand -relief sunken -width 12
         install azachieved using ttk::label $azel.azachieved -relief sunken \
               -width 12
         install azdiff using ttk::label $azel.azdiff -relief sunken -width 10
         install azstatus using tif::status $azel.azstatus \
               -width 12 -height 12 -borderwidth 3
         install ellabel using ttk::label $azel.ellabel -text Elevation: -anchor e
         install eldemand using ttk::label $azel.eldemand -relief sunken
         install elachieved using ttk::label $azel.elachieved -relief sunken 
         install eldiff using ttk::label $azel.eldiff -relief sunken
         install elstatus using tif::status $azel.elstatus \
               -width 12 -height 12 -borderwidth 3
         install rotlabel using ttk::label $azel.rotlabel -text Rotator: -anchor e
         install rotdemand using ttk::label $azel.rotdemand -relief sunken
         install rotachieved using ttk::label $azel.rotachieved -relief sunken 
         install rotdiff using ttk::label $azel.rotdiff -relief sunken
         install rotstatus using tif::status $azel.rotstatus \
               -width 12 -height 12 -borderwidth 3
         install tiplabel using ttk::label $azel.tiplabel -text "Tip:" -anchor e
         install tipdemand using ttk::label $azel.tipdemand -relief sunken
         install tipachieved using ttk::label $azel.tipachieved -relief sunken 
         install tipdiff using ttk::label $azel.tipdiff -relief sunken
         install tiltlabel using ttk::label $azel.tiltlabel -text "Tilt:" -anchor e
         install tiltdemand using ttk::label $azel.tiltdemand -relief sunken
         install tiltachieved using ttk::label $azel.tiltachieved -relief sunken 
         install tiltdiff using ttk::label $azel.tiltdiff -relief sunken
         install gxlabel using ttk::label $azel.gxlabel -text "Guider X:" -anchor e
         install gxdemand using ttk::label $azel.gxdemand -relief sunken
         install gxachieved using ttk::label $azel.gxachieved -relief sunken 
         install gxdiff using ttk::label $azel.gxdiff -relief sunken
         install gylabel using ttk::label $azel.gylabel -text Y: -anchor e
         install gydemand using ttk::label $azel.gydemand -relief sunken
         install gyachieved using ttk::label $azel.gyachieved -relief sunken 
         install gydiff using ttk::label $azel.gydiff -relief sunken

         grid x $demand $achieved $diff
         grid $azlabel $azdemand $azachieved $azdiff $azstatus -sticky ew
         grid $ellabel $eldemand $elachieved $eldiff $elstatus -sticky ew
         grid $rotlabel $rotdemand $rotachieved $rotdiff $rotstatus -sticky ew
         grid $tiplabel $tipdemand $tipachieved $tipdiff -sticky ew
         grid $tiltlabel $tiltdemand $tiltachieved $tiltdiff -sticky ew
         grid $gxlabel $gxdemand $gxachieved $gxdiff -sticky ew
         grid $gylabel $gydemand $gyachieved $gydiff -sticky ew

      # Build the complete panel
         pack $pos -side top -anchor w
         pack $azel -side top

         $self configurelist $args
      }
      method update {args} {

      # Update all the widgets with the latest kernel status.
         $tarpos configure -text $tpk::target_position($options(-mount))
         $telpos configure -text $tpk::telescope_position($options(-mount))
         $fieldorient configure -text \
               [format %9.4f $tpk::field_orientation($options(-mount))]
         $azdemand configure -text [format %9.4f $tpk::az_demand]
         $azachieved configure -text [format %9.4f $tpk::az]
         $azdiff configure -text \
               [format %+9.4f [expr {$tpk::az_demand - $tpk::az}]]
         $azstatus configure -status \
               [expr {$tpk::az_in_position ? "ok" : "warn"}]
         $eldemand configure -text [format "%9.4f" $tpk::el_demand]
         $elachieved configure -text [format %9.4f $tpk::el]
         $eldiff configure -text \
               [format %+9.4f [expr {$tpk::el_demand - $tpk::el}]]
         $elstatus configure -status \
               [expr {$tpk::el_in_position ? "ok" : "warn"}]
         $rotdemand configure -text [format %9.4f \
               $tpk::rma_demand($options(-mount))]
         $rotachieved configure -text \
               [format %9.4f $tpk::rma($options(-mount))]
         $rotdiff configure -text [format %+9.4f [expr \
               {$tpk::rma_demand($options(-mount)) - \
               $tpk::rma($options(-mount))}]]
         $rotstatus configure -status \
               [expr {$tpk::rot_in_position($options(-mount)) ? "ok" : "warn"}]
         $tipdemand configure -text \
               [format %9.3f $tpk::tip_demand($options(-mount))]
         $tipachieved configure -text \
               [format %9.3f $tpk::tip($options(-mount))]
         $tipdiff configure -text [format %+9.3f \
               [expr {$tpk::tip_demand($options(-mount)) - \
                $tpk::tip($options(-mount))}]]
         $tiltdemand configure -text \
               [format %9.3f $tpk::tilt_demand($options(-mount))]
         $tiltachieved configure -text \
               [format %9.3f $tpk::tilt($options(-mount))]
         $tiltdiff configure -text [format %+9.3f \
               [expr {$tpk::tilt_demand($options(-mount)) - \
                $tpk::tilt($options(-mount))}]]
         $gxdemand configure -text \
               [format %9.3f $tpk::xguider_demand($options(-guider))]
         $gxachieved configure -text \
               [format %9.3f $tpk::xguider($options(-guider))]
         $gxdiff configure -text [format %+9.3f \
               [expr {$tpk::xguider_demand($options(-guider)) - \
                $tpk::xguider($options(-guider))}]]
         $gydemand configure -text \
               [format %9.3f $tpk::yguider_demand($options(-guider))]
         $gyachieved configure -text \
               [format %9.3f $tpk::yguider($options(-guider))]
         $gydiff configure -text [format %+9.3f \
               [expr {$tpk::yguider_demand($options(-guider)) - \
                     $tpk::yguider($options(-guider))}]]
      }
   }
}
