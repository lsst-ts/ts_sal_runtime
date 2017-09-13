set PI 3.14159265358979
set D2R [expr $PI/180.]
set LAT [expr 32.0*$D2R]


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



