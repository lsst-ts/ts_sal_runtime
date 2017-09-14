


// This file contains the implementation for the camera_start commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_startTest extends TestCase {

   	public cameraCommander_startTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_start() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_start");
	    camera.command_start command  = new camera.command_start();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "configuration";
            command.property = "set";
            command.action   = "apply";
            command.configuration = "testing";

	    cmdId = mgr.issueCommand_start(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_start(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


