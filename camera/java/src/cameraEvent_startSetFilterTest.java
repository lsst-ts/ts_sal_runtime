


// This file contains the implementation for the camera_startSetFilter event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_startSetFilterTest extends TestCase {

   	public cameraEvent_startSetFilterTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_startSetFilter () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_startSetFilter");
            int priority=1;
	    camera.logevent_startSetFilter event  = new camera.logevent_startSetFilter();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_startSetFilter(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


