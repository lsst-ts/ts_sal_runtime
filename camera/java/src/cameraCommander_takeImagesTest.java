


// This file contains the implementation for the camera_takeImages commander test.
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander_takeImagesTest extends TestCase {

   	public cameraCommander_takeImagesTest(String name) {
   	   super(name);
   	}

	public void testcameraCommander_takeImages() {

	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;


            int timeout=3;

  	    mgr.salCommand("camera_command_takeImages");
	    camera.command_takeImages command  = new camera.command_takeImages();

	    command.private_revCode = "LSST TEST COMMAND";
            command.device   = "takeImages";
            command.property = "";
            command.action   = "";
            command.numImages = (int) 1;
            command.expTime = (double) 1.0;
            command.shutter = true;
            command.science = true;
            command.guide = true;
            command.wfs = true;
            command.imageSequenceName = "testing";

	    cmdId = mgr.issueCommand_takeImages(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion_takeImages(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

      }

}


