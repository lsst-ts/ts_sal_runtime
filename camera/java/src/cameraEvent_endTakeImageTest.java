


// This file contains the implementation for the camera_endTakeImage event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_endTakeImageTest extends TestCase {

   	public cameraEvent_endTakeImageTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_endTakeImage () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_endTakeImage");
            int priority=1;
	    camera.logevent_endTakeImage event  = new camera.logevent_endTakeImage();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_endTakeImage(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


