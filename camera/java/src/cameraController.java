

import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraController {

	public static void main(String[] args) {
          short aKey   = 1;
	  int status   = SAL_camera.SAL__OK;
	  int cmdId    = 0;
          int timeout  = 0;
          boolean finished=false;

	  // Initialize
	  SAL_camera cmd = new SAL_camera();

          if (args.length > 0) {
             timeout=Integer.parseInt(args[0]) * 1000;
          }

	  cmd.salProcessor();
	  camera.command command = new camera.command();

	  while (!finished) {

	     cmdId = cmd.acceptCommand(command);
	     if (cmdId > 0) {
	       if (timeout > 0) {
	          cmd.ackCommand(cmdId, SAL_camera.SAL__CMD_INPROGRESS, timeout, "Ack : OK");
 	          try {Thread.sleep(timeout);} catch (InterruptedException e)  { e.printStackTrace(); }
	       }       
	       cmd.ackCommand(cmdId, SAL_camera.SAL__CMD_COMPLETE, 0, "Done : OK");
	     }
 	     try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  cmd.salShutdown();
       }
}


