
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_endInitializeImageTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_endInitializeImage");
	  camera.logevent_endInitializeImage event = new camera.logevent_endInitializeImage();
          System.out.println("Event endInitializeImage logger ready ");

	  while (!finished) {
	     status = evt.getEvent_endInitializeImage(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

