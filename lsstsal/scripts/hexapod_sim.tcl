#
#  Calculate the camera and m2 hexapod motions  based on azimuth and elevation
#
set tcl_precision 8

proc hexcalc { device e} {
  set PI      3.14159265359
  if { $device == "camera" } {

	set E7     -0.19930118
	set F7  -1324.68205
	set G7     -9.5013145
	set H7     -0.0354691
	set I7     -0.000008631
	set J7     -0.000007396
	set E14     1.656270415
	set F14   -29.83178649
	set G14  -910.2272456
	set H14     0.0000116088
	set I14    -0.0000098319
	set J14    -0.0000568789

# elevation is A($e) = e in degrees

# camera hexapod ------------------------------------------------------------
# camera zenith components
	set D($e) [expr 90-$e]
	set C($e) [expr $D($e)*$PI/180.]	
	set E($e) [expr cos($C($e))*$E14]
	set F($e) [expr cos($C($e))*$F14]
	set G($e) [expr cos($C($e))*$G14] 
	set H($e) [expr cos($C($e))*$H14]
	set I($e) [expr cos($C($e))*$I14] 
	set J($e) [expr cos($C($e))*$J14] 	
#puts stdout "camera zenith $D($e) $E($e) $F($e) $G($e) $H($e) $I($e) $J($e)"

# camera horizon compomnents
	set N($e) [expr sin($C($e))*$E7]
	set O($e) [expr sin($C($e))*$F7]
	set P($e) [expr sin($C($e))*$G7]
	set Q($e) [expr sin($C($e))*$H7]
	set R($e) [expr sin($C($e))*$I7]
	set S($e) [expr sin($C($e))*$J7]
#puts stdout "camera horizon $N($e) $O($e) $P($e) $Q($e) $R($e) $S($e)"

# camera combined comps
	set W($e)  [expr $E($e) + $N($e)]
	set X($e)  [expr $F($e) + $O($e)]
	set Y($e)  [expr $G($e) + $P($e)]
	set Z($e)  [expr $H($e) + $Q($e)]
	set AA($e) [expr $I($e) + $R($e)]
	set AB($e) [expr $J($e) + $S($e)]
#puts stdout "Camera combined $W($e) $X($e) $Y($e) $Z($e) $AA($e) $AB($e)"

	return "$W($e) $X($e) $Y($e) $Z($e) $AA($e) $AB($e)"

   } else {

# m2 hexapod ------------------------------------------------------------
	set E6      4.7022581
	set F6  -1173.5712
	set G6    -73.8183775
	set H6     -0.01315978
	set I6      0.00001253
	set J6     -0.00009770
	set E13     9.48870708
	set F13   -44.3076436
	set G13 -1035.480953
	set H13     0.0001940386 
	set I13    -0.0000423753 
	set J13    -0.0002111026 

# m2 elevation components
	set D($e) [expr 90-$e]
	set C($e) [expr $D($e)*$PI/180.]
	set E($e) [expr cos($C($e))*$E13] 
	set F($e) [expr cos($C($e))*$F13] 
	set G($e) [expr cos($C($e))*$G13] 
	set H($e) [expr cos($C($e))*$H13] 
	set I($e) [expr cos($C($e))*$I13]
	set J($e) [expr cos($C($e))*$J13]
#puts stdout "m2 elevation $E($e) $F($e) $G($e) $H($e) $I($e) $J($e)"

# m2 horizon compomnents
	set N($e) [expr sin($C($e))*$E6]
	set O($e) [expr sin($C($e))*$F6]
	set P($e) [expr sin($C($e))*$G6]
	set Q($e) [expr sin($C($e))*$H6]
	set R($e) [expr sin($C($e))*$I6]
	set S($e) [expr sin($C($e))*$J6]
#puts stdout "m2 horizon $N($e) $O($e) $P($e) $Q($e) $R($e) $S($e)"

# m2 combined comps
	set W($e)  [expr $E($e) + $N($e)]
	set X($e)  [expr $F($e) + $O($e)]
	set Y($e)  [expr $G($e) + $P($e)]
	set Z($e)  [expr $H($e) + $Q($e)]
	set AA($e) [expr $I($e) + $R($e)]
	set AB($e) [expr $J($e) + $S($e)]
#puts stdout "m2 combined $W($e) $X($e) $Y($e) $Z($e) $AA($e) $AB($e)"
	return "$W($e) $X($e) $Y($e) $Z($e) $AA($e) $AB($e)"
  }

}

