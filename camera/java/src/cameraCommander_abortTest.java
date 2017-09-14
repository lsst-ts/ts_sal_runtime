


// This file contains the implementation for the camera_abort commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_abortTest extends TestCase {

   	public cameraCommander_abortTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_abort() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_abort");
	    camera.command_abort command  = new camera.command_abort();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "all";
            command.property = "abort";
            command.action   = "";
            command.state = true;

	    cmdId = mgr.issueCommand_abort(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_abort(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


