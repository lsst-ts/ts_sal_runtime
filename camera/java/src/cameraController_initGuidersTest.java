
package org.lsst.sal.junit.camera;

import junit.framework.TestCase;
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraController_initGuidersTest extends TestCase {

   	public cameraController_initGuidersTest(String name) {
   	   super(name);
   	}

	public void testcameraController_initGuiders() {
          short aKey   = 1;
	  int status   = SAL_camera.SAL__OK;
	  int cmdId    = 0;
          int timeout  = 3;
          boolean finished=false;

	  // Initialize
	  SAL_camera cmd = new SAL_camera();

	  cmd.salProcessor("camera_command_initGuiders");
	  camera.command_initGuiders command = new camera.command_initGuiders();
          System.out.println("camera_initGuiders controller ready ");

	  while (!finished) {

	     cmdId = cmd.acceptCommand_initGuiders(command);
	     if (cmdId > 0) {
	       if (timeout > 0) {
	          cmd.ackCommand_initGuiders(cmdId, SAL_camera.SAL__CMD_INPROGRESS, 0, "Ack : OK");
 	          try {Thread.sleep(timeout);} catch (InterruptedException e)  { e.printStackTrace(); }
	       }       
	       cmd.ackCommand_initGuiders(cmdId, SAL_camera.SAL__CMD_COMPLETE, 0, "Done : OK");
               finished = true;
	     }
             timeout = timeout-1;
             if (timeout == 0) {
               finished = true;
             }
 	     try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  cmd.salShutdown();
       }
}


