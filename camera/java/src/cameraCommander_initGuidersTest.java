


// This file contains the implementation for the camera_initGuiders commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_initGuidersTest extends TestCase {

   	public cameraCommander_initGuidersTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_initGuiders() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_initGuiders");
	    camera.command_initGuiders command  = new camera.command_initGuiders();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "initGuiders";
            command.property = "";
            command.action   = "";
            command.roiSpec = "testing";

	    cmdId = mgr.issueCommand_initGuiders(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_initGuiders(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


