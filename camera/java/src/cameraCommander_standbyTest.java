


// This file contains the implementation for the camera_standby commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_standbyTest extends TestCase {

   	public cameraCommander_standbyTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_standby() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_standby");
	    camera.command_standby command  = new camera.command_standby();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "controller";
            command.property = "command";
            command.action   = "stop";
            command.state = true;

	    cmdId = mgr.issueCommand_standby(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_standby(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


