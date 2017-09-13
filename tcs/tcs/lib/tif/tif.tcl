package require Tcl 8.4
package require Tk 8.4
package require Thread 2.4
package require tile
package require snit 1.1

namespace eval tif {
   namespace export *
}

source [file join [file dirname [info script]] console.tcl]
source [file join [file dirname [info script]] interface.tcl]
source [file join [file dirname [info script]] camera.tcl]
source [file join [file dirname [info script]] mountview.tcl]
source [file join [file dirname [info script]] skyplot.tcl]
source [file join [file dirname [info script]] status.tcl]
source [file join [file dirname [info script]] strip.tcl]
source [file join [file dirname [info script]] tcs.tcl]
source [file join [file dirname [info script]] timeview.tcl]
source [file join [file dirname [info script]] tracktime.tcl]

package provide Tif 1.0.0
