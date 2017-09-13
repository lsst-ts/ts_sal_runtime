namespace eval tif {
   snit::widget timeview {
      component date
      component stlabel
      component st
      delegate option * to hull
      constructor {args} {

         install date using ttk::label $win.date -width 20
         install stlabel using ttk::label $win.stlabel -text ST:
         install st using ttk::label $win.st -width 10
         grid $date $stlabel $st
         grid configure $date -padx 20

         $self configurelist $args
      }
      method update {args} {

      # Update the widgets with the latest kernel status.
         $date configure -text $tpk::tai_string
         $st configure -text $tpk::st_string
      }
   }
}
