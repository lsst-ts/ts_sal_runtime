


// This file contains the implementation for the camera_stop commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_stopTest extends TestCase {

   	public cameraCommander_stopTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_stop() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_stop");
	    camera.command_stop command  = new camera.command_stop();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "all";
            command.property = "motion";
            command.action   = "stop";
            command.state = true;

	    cmdId = mgr.issueCommand_stop(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_stop(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


