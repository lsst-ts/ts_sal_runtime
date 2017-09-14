


// This file contains the implementation for the camera_exitControl commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_exitControlTest extends TestCase {

   	public cameraCommander_exitControlTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_exitControl() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_exitControl");
	    camera.command_exitControl command  = new camera.command_exitControl();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "controller";
            command.property = "command";
            command.action   = "exit";
            command.state = true;

	    cmdId = mgr.issueCommand_exitControl(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_exitControl(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


