


// This file contains the implementation for the camera_ccsConfigured event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_ccsConfiguredTest extends TestCase {

   	public cameraEvent_ccsConfiguredTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_ccsConfigured () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_ccsConfigured");
            int priority=1;
	    camera.logevent_ccsConfigured event  = new camera.logevent_ccsConfigured();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_ccsConfigured(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


