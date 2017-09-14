
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_endTakeImageTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_endTakeImage");
	  camera.logevent_endTakeImage event = new camera.logevent_endTakeImage();
          System.out.println("Event endTakeImage logger ready ");

	  while (!finished) {
	     status = evt.getEvent_endTakeImage(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

