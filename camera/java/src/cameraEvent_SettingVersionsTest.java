


// This file contains the implementation for the camera_SettingVersions event generator test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent_SettingVersionsTest extends TestCase {

   	public cameraEvent_SettingVersionsTest(String name) {
   	   super(name);
   	}

	public void testcameraEvent_SettingVersions () {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue Event
          int status=0;

            mgr.salEvent("camera_logevent_SettingVersions");
            int priority=1;
	    camera.logevent_SettingVersions event  = new camera.logevent_SettingVersions();
	    event.private_revCode = "LSST TEST EVENT";
  	    event.recommendedSettingVersion = "testing";
   	    event.priority = (int) 1;

	    status = mgr.logEvent_SettingVersions(event,priority);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


