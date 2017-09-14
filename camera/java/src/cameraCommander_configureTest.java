


// This file contains the implementation for the camera_configure commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_configureTest extends TestCase {

   	public cameraCommander_configureTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_configure() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_configure");
	    camera.command_configure command  = new camera.command_configure();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "configure";
            command.property = "";
            command.action   = "";
            command.specId = "testing";

	    cmdId = mgr.issueCommand_configure(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_configure(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


