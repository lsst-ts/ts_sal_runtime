
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_ccsConfiguredTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_ccsConfigured");
	  camera.logevent_ccsConfigured event = new camera.logevent_ccsConfigured();
          System.out.println("Event ccsConfigured logger ready ");

	  while (!finished) {
	     status = evt.getEvent_ccsConfigured(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

