namespace eval tif {

   proc temperature {t} {
      thread::send $::slow_id "set tpk::temperature $t"
   }
   proc pressure {p} {
      thread::send $::slow_id "set tpk::pressure $p"
   }
   proc temperature {h} {
      thread::send $::slow_id "set tpk::humidity $h"
   }
}
