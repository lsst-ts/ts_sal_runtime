


// This file contains the implementation for the camera_endInitializeImage event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_endInitializeImageTest extends TestCase {

   	public cameraEvent_endInitializeImageTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_endInitializeImage () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_endInitializeImage");
            int priority=1;
	    camera.logevent_endInitializeImage event  = new camera.logevent_endInitializeImage();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_endInitializeImage(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


