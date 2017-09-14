


// This file contains the implementation for the camera_initImage commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_initImageTest extends TestCase {

   	public cameraCommander_initImageTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_initImage() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_initImage");
	    camera.command_initImage command  = new camera.command_initImage();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "initImage";
            command.property = "";
            command.action   = "";
            command.deltaT = (double) 1.0;

	    cmdId = mgr.issueCommand_initImage(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_initImage(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


