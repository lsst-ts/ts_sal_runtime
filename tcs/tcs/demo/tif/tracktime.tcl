namespace eval tpk {
    proc tracktime {} {
        set reason [lindex $::limittime 0]
        set t [lindex $::limittime 1]
        if {$reason eq "none"} {
            return ""
        } else {
            switch $reason {
               azlow {set reason "Azimuth low limit"}
               azhigh {set reason "Azimuth high limit"}
               horizon {set reason "Horizon limit"}
               zenith {set reason "Zenith limit"}
               rotlow {set reason "Rotator low limit"}
               rothigh {set reason "Rotator high limit"}
            }
        }
        set dth [expr {($t - $tpk::tai) * 24.0}]
        if { $dth <= 0.0 } {
            return $reason
        }
        if { $dth >= 1.0 } {
            return [format "%s in %3.1f hours" $reason $dth]
        }
        set dtm [expr {$dth * 60.0}]
        if { $dtm >= 1.0 } {
           return [format "%s in %4.1f minutes" $reason $dtm]
        }
        set dts [expr {int($dtm * 60.0)}]
        return [format "%s in %2d seconds" $reason $dts]
    }
}
