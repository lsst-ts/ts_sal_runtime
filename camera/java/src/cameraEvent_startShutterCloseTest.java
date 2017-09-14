


// This file contains the implementation for the camera_startShutterClose event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_startShutterCloseTest extends TestCase {

   	public cameraEvent_startShutterCloseTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_startShutterClose () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_startShutterClose");
            int priority=1;
	    camera.logevent_startShutterClose event  = new camera.logevent_startShutterClose();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_startShutterClose(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


