


// This file contains the implementation for the camera_SetValue commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_SetValueTest extends TestCase {

   	public cameraCommander_SetValueTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_SetValue() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_SetValue");
	    camera.command_SetValue command  = new camera.command_SetValue();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "controller";
            command.property = "configuration";
            command.action   = "set";
            command.json_parameters = "testing";

	    cmdId = mgr.issueCommand_SetValue(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_SetValue(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


