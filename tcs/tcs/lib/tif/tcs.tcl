# Create the fast loop procedure.
    proc fast-loop {} {
        tpk::fast
        tpk::stats
        after 50 fast-loop
    }

namespace eval tif {

    proc tcsInit {telname} {

        set libname $telname[info sharedlibextension]

     # Search for the tcl extension.
        set libpath [list ./ [file dirname [info script]] \
                      [file join [file dirname [info script]] ../lib]]
        if { ! [info exists ::env(TPK_EXTENSION)] } {
            foreach dir $libpath {
                if { [file exists [file join $dir $libname]] } {
                   set ::env(TPK_EXTENSION) [file join $dir $libname]
                   break;
                }
            }
        }        
        if { ! [info exists ::env(TPK_EXTENSION)] } {
           error "Can't find tpk loadable extension"
        }

    # Search for the planet ephemeris files and define the variable
    # that points at them.
        set datapath [list [file dirname [info script]] \
                      [file join [file dirname [info script]] ../data] \
                      [file join [file dirname [info script]] ../etc]]
        foreach dir $datapath {
            if { [file exists [file join $dir series96.mer]] } {
                set ephempath $dir
                break;
            }
        }        
        if { ! [info exists ephempath] } {
           error "Can't find planetary ephemeris files"
        }


    # Load the extension into this interpreter.
        namespace eval :: {load $::env(TPK_EXTENSION) tpk}

    # Set the ephemeris path
        tpk::ephempath [file nativename $ephempath]

    # Create an interpreter in a new thread for running the slow loop.
        set ::slow_id [thread::create {

        # Load the extension.
               load $::env(TPK_EXTENSION) tpk

        # Define a procedure to execute the slow processing.
           proc slow-loop {} {

           # Do the slow processing.
              tpk::slow

           # Schedule again in 1 minute's time.
              after 60000 slow-loop
           }

        # Start the event loop
           thread::wait
        }]

    # Create an interpreter in a new thread for running the medium loop.
        set ::medium_id [thread::create {
           load $::env(TPK_EXTENSION) tpk
           proc medium-loop {} {
              tpk::medium
              after 10000 medium-loop
           }
           thread::wait
        }]

    # Start the slow loop.
        thread::send -async $::slow_id slow-loop

    # Start the medium loop.
        thread::send -async $::medium_id medium-loop
    }
}
