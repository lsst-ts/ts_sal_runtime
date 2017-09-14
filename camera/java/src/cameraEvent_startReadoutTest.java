


// This file contains the implementation for the camera_startReadout event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_startReadoutTest extends TestCase {

   	public cameraEvent_startReadoutTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_startReadout () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_startReadout");
            int priority=1;
	    camera.logevent_startReadout event  = new camera.logevent_startReadout();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_startReadout(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


