


// This file contains the implementation for the camera_SummaryState event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_SummaryStateTest extends TestCase {

   	public cameraEvent_SummaryStateTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_SummaryState () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_SummaryState");
            int priority=1;
	    camera.logevent_SummaryState event  = new camera.logevent_SummaryState();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.SummaryStateValue = (int) 1;
   	    event.priority = (int) 1;

	    status = mgr.logEvent_SummaryState(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


