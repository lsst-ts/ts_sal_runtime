


// This file contains the implementation for the camera_ErrorCode event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_ErrorCodeTest extends TestCase {

   	public cameraEvent_ErrorCodeTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_ErrorCode () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_ErrorCode");
            int priority=1;
	    camera.logevent_ErrorCode event  = new camera.logevent_ErrorCode();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.errorCode = (int) 1;
   	    event.priority = (int) 1;

	    status = mgr.logEvent_ErrorCode(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


