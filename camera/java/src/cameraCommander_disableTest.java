


// This file contains the implementation for the camera_disable commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_disableTest extends TestCase {

   	public cameraCommander_disableTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_disable() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_disable");
	    camera.command_disable command  = new camera.command_disable();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "controller";
            command.property = "command";
            command.action   = "";
            command.state = true;

	    cmdId = mgr.issueCommand_disable(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_disable(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


