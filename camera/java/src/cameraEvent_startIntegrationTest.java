


// This file contains the implementation for the camera_startIntegration event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_startIntegrationTest extends TestCase {

   	public cameraEvent_startIntegrationTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_startIntegration () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_startIntegration");
            int priority=1;
	    camera.logevent_startIntegration event  = new camera.logevent_startIntegration();
	    event.private_revCode = "LSST TEST EVENT";
  	    event.imageName = "testing";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_startIntegration(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


