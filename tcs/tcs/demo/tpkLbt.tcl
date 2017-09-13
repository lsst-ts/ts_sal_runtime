# Start the LBT demonstration telescope.

# Add the location of the telecope interface package to the list of locations
# searched when loading packages.
lappend auto_path ./
lappend auto_path [file join [file dirname [info script]] ../lib]

# Load the telescope interface package.
package require Tif

# Create and start the pointing kernel
tif::tcsInit tpkLbt

# Create the top level windows for the TV displays.
toplevel .cam_left
grid [tif::camera .cam_left.ccd -mount left -guider left]
wm resizable .cam_left 0 0 
toplevel .cam_right
grid [tif::camera .cam_right.ccd -mount right -guider right]
wm resizable .cam_right 0 0 

# Layout the display GUI.
grid [frame .frame -borderwidth 2 -relief sunken]
grid [tif::timeview .frame.time]
grid [tif::mountview .frame.mount_left \
      -mount left -guider left] \
      [tif::skyplot .frame.skyplot -width 250 -height 250] \
      [tif::mountview .frame.mount_right \
      -mount right -guider right]
grid .frame.time -columnspan 3
wm resizable . 0 0

proc refresh {args} {

# Update the time display.
   .frame.time update

# Update the mount display.
   .frame.mount_left update
   .frame.mount_right update

# Configure the TV displays with the actual position of the mount.
   .frame.skyplot configure -position [list $tpk::az $tpk::el]
   .frame.skyplot configure -demand [list $tpk::az_demand $tpk::el_demand]

# Re-draw the star field.
   .cam_left.ccd reposition
   .cam_right.ccd reposition
}

# Trigger refresh each time the $fast loop runs.
   trace add execution fast-loop leave refresh

# Run the fast loop for the first time.
fast-loop

# This procedure checks to see if the mount is in position and if it is it
# sets the optics mode to "track_mount".
proc check_mount {} {
   if { $tpk::az_in_position && $tpk::el_in_position } {
      tpk::optics track_mount 1
   } else {
      after 1000 check_mount
   }
}

# This procedure slews the telescope by setting the specified target in the
# mount and the virtual telescope that calculates the positions of the
# artifical stars in the focal plane and generates a new star field centred
# on the new target.
proc slew {target} {

# Set the wrap flags to move away from the limits
   tpk::wrap azimuth nearestrange achieved 0
   tpk::wrap rotator_left nearestrange achieved 0
   tpk::wrap rotator_right nearestrange achieved 0

# Turn off the optics "track_mount" mode.
   tpk::optics track_mount 0

# Load the new target into mount and optics virtual telescopes.
   tpk::target set left $target
   tpk::target set right $target
   tpk::target set optics_left $target
   tpk::target set optics_right $target

# Set the "sky" targets.
   tpk::target set sky_left $target
   tpk::target set sky_right $target

# Generate a new star field with 10 stars in it.
   set field [tpk::skysample left 10]

# Create targets for each of the artifical stars so that we can use them
# as guide stars.
   for { set i 1 } { $i < [llength $field] } { incr i } {
      catch {tpk::target delete gs$i}
      tpk::target create icrs [lindex $field $i] gs$i
   }

# Starting checking for the end of the slew.
   after 1000 check_mount

# Return the ICRS position of the field centre.
   return [lindex $field 0]
}

proc wavelength {tel val} {
   tpk::wavelength $tel $val
   if { $tel eq "left" || $tel eq "right" } {
      tpk::wavelength optics_$tel $val
      tpk::wavelength sky_$tel $val
   }
}

proc pointingmodel {tel val} {
   tpk::pointingmodel $tel $val
   if { $tel eq "left" || $tel eq "right" } {
      tpk::pointingmodel sky_$tel $val
   }
}

proc offset {tel opt args} {
   if { $opt ne "enable" && $opt ne "disable" } {
      eval tpk::offset $tel $opt $args
      if { $tel eq "left" || $tel eq "right" } {
         eval tpk::offset optics_$tel $opt $args
      }
   } else {
      tpk::offset $tel $opt
      if { $tel eq "left" || $tel eq "right" } {
         tpk::offset optics_$tel $opt
      }
   }
}
      
proc origin {opt args} {
   if { $opt eq "set" } {
      eval tpk::origin set $args
      if { [lindex $args 0] eq "left" || [lindex $args 0] eq "right" } {
         tpk::origin set optics_[lindex $args 0] [lindex $args 1]
      }
   } else {
      eval tpk::origin $opt $args
   }
}

# This procedure enables all the axes.
proc enable {} {
   foreach axis [tpk::telinfo axes] {
      tpk::axis $axis enable
   }
}
      
namespace eval tpk:: {namespace export *}
namespace import tpk::axis
namespace import tpk::guide
namespace import tpk::ipa
namespace import tpk::optics
namespace import tpk::pointing
namespace import tpk::target
namespace import tpk::telinfo
