

import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEvent {

	public static void main(String[] args) {


	  // Initialize
          int status=0;
          short aKey=1;
	  SAL_camera mgr = new SAL_camera();
	  
          if (args.length < 3) {

            System.err.println("Usage: alias message modifiers");
            System.exit(1);

          } else {

	    String msg=args[1] + " " + args[2];
	    int priority=1;
	    status = mgr.logEvent(msg,priority);
            try {Thread.sleep(1000);} catch (InterruptedException e) { e.printStackTrace(); }

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

	  }
       }

}

