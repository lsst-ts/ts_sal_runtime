


// This file contains the implementation for the camera_startLoadFilter event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_startLoadFilterTest extends TestCase {

   	public cameraEvent_startLoadFilterTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_startLoadFilter () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_startLoadFilter");
            int priority=1;
	    camera.logevent_startLoadFilter event  = new camera.logevent_startLoadFilter();
	    event.private_revCode = "LSST TEST EVENT";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_startLoadFilter(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


