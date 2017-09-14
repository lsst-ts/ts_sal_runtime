
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_startShutterCloseTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_startShutterClose");
	  camera.logevent_startShutterClose event = new camera.logevent_startShutterClose();
          System.out.println("Event startShutterClose logger ready ");

	  while (!finished) {
	     status = evt.getEvent_startShutterClose(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

