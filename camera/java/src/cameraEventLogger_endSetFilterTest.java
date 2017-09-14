
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_endSetFilterTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_endSetFilter");
	  camera.logevent_endSetFilter event = new camera.logevent_endSetFilter();
          System.out.println("Event endSetFilter logger ready ");

	  while (!finished) {
	     status = evt.getEvent_endSetFilter(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

