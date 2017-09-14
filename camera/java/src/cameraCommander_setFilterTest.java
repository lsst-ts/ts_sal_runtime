


// This file contains the implementation for the camera_setFilter commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_setFilterTest extends TestCase {

   	public cameraCommander_setFilterTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_setFilter() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_setFilter");
	    camera.command_setFilter command  = new camera.command_setFilter();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "setFilter";
            command.property = "";
            command.action   = "";
            command.name = "testing";

	    cmdId = mgr.issueCommand_setFilter(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_setFilter(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


