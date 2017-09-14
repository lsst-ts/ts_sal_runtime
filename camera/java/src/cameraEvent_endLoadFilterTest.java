


// This file contains the implementation for the camera_endLoadFilter event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_endLoadFilterTest extends TestCase {

   	public cameraEvent_endLoadFilterTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_endLoadFilter () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_endLoadFilter");
            int priority=1;
	    camera.logevent_endLoadFilter event  = new camera.logevent_endLoadFilter();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_endLoadFilter(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


