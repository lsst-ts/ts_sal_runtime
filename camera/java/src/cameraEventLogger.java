

import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger {

	public static void main(String[] args) {
          short aKey   = 1;
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
	  camera.logevent event = new camera.logevent();

	  while (!finished) {
	     status = evt.getEvent(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event.message);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}


