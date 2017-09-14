


// This file contains the implementation for the camera_enterControl commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_enterControlTest extends TestCase {

   	public cameraCommander_enterControlTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_enterControl() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_enterControl");
	    camera.command_enterControl command  = new camera.command_enterControl();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "controller";
            command.property = "command";
            command.action   = "allow";
            command.state = true;

	    cmdId = mgr.issueCommand_enterControl(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_enterControl(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


