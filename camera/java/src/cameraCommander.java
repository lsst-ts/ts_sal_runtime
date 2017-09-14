

import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraCommander {

	public static void main(String[] args) {

          short aKey=1;
	  SAL_camera mgr = new SAL_camera();

	  // Issue command
	  int count=0;
          int cmdId=0;
          int status=0;

          if (args.length < 6) {

            System.err.println("Usage: timeout device property action value modifiers");
            System.exit(1);

          } else {

            int timeout=Integer.parseInt(args[0]);

  	    mgr.salCommand();
	    camera.command command  = new camera.command();

	    command.private_revCode = "LSST TEST COMMAND";
	    command.device =    args[1];
	    command.property =  args[2];
	    command.action =    args[3];
	    command.value =     args[4];
	    command.modifiers = args[5];

	    cmdId = mgr.issueCommand(command);

	    try {Thread.sleep(1000);} catch (InterruptedException e)  { e.printStackTrace(); }
	    status = mgr.waitForCompletion(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

	}
      }

}

