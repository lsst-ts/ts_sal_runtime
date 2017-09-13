#!/usr/bin/tclsh
set PI 3.14159265358979
set D2R [expr $PI/180.]
set LAT [expr 32.0*$D2R]
set tcl_precision 15

proc hadecToaltaz { ha dec } {
global LAT PI D2R
  set sh [expr sin($ha*$D2R)]
  set ch [expr cos($ha*$D2R)]
  set sd [expr sin($dec*$D2R)]
  set cd [expr cos($dec*$D2R)]
  set sl [expr sin($LAT*$D2R)]
  set cl [expr cos($LAT*$D2R)]
  set x [expr -$ch * $cd * $sl * $cl]
  set y [expr -$sh * $cd]
  set z [expr $ch * $cd + $sd * $sl]
  set r [expr sqrt($x*$x + $y*$y)]
  set az  [expr atan2($y,$x) / $D2R]
  set alt [expr atan2($z,$r) / $D2R]
  return "$az $alt"
}

load $env(SAL_DIR)/../lib/libxtcs.so

set fin1 [open kraken1042.1.txt r]
set fin2 [open kraken1042.2.txt r]
set fout [open rotator_commands.dat w]
set count 0 
set visits 200
set startvisit 700
set lastfield 0
set lastfilter r
set ts 1356566417.0000000000
gets $fin1 rec
gets $fin1 rec
gets $fin1 rec
gets $fin1 rec
gets $fin2 rec
gets $fin2 rec
gets $fin2 rec
gets $fin2 rec
while { $count < $startvisit } {gets $fin1 rec ; gets $fin2 rec2 ; incr count 1}
set count 0
while { $count < $visits}  {
   gets $fin1 rec
   gets $fin2 rec2
   set flds [split $rec "|"]
   set flds2 [split $rec2 "|"]
   set field [lindex $flds 1]
#   if { $field != $lastfield } {
      incr count 1
      set lastfield $field
      set filter [lindex $flds2 5]
      if { $filter != $lastfilter} {
        puts stdout "FILTER CHANGE"
        set lastfilter $filter
      }
        set lastfilter $filter
#      set mjd [lindex $rec 9]
#      set exptime [lindex $rec 10]
#      set slewtime [lindex $rec 11]
        set slewtime [lindex $flds 4]
        set dec [expr 50.0*$D2R]
        set rot [expr [lindex $flds2 4]/3.1415926535*180.0]
        set alt [lindex $flds2 3]
        set altdeg [expr $alt/3.1415926535*180.0]
        set az  [lindex $flds2 2]
        set azdeg [expr $az/3.1415926535*180.0]
# Observers constant k in degress per second, rotrate in deg per 50msec
        puts stdout "Field $field at $altdeg, $azdeg,  cos(alt)=[expr cos($alt)]"
        set k [expr 15.04106858 * cos(-30.7494/180.*3.14159365) / 3600.]
        set rotrate [expr ($k * cos($az) / cos($alt))/20.0]
        set i 0
        set iloop [expr int($slewtime * 20)]
        while { $i < $iloop } {
         puts $fout "[format %10.3f $ts] [format %10.7f $rot] [format %16.12f [expr $rotrate * 20]]"
         incr i 1
         set az [expr $az + 5.787037037037037e-7]
         set rotrate [expr ($k * cos($az) / cos($alt))/20.0]
         set rot [expr $rot + $rotrate]
         set ts  [expr $ts + 0.05000000]
        }
        set i 0
        while { $i < 32*20 } {
         puts $fout "[format %10.3f $ts] [format %10.7f $rot] [format %16.12f [expr $rotrate * 20]]"
         incr i 1
         set az [expr $az + 5.787037037037037e-7]
         set rotrate [expr ($k * cos($az) / cos($alt))/20.0]
         set rot [expr $rot + $rotrate]
         set ts  [expr $ts + 0.05000000]
        }
#  }
}
close $fin1
close $fin2
close $fout

