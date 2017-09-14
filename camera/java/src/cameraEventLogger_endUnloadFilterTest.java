
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_endUnloadFilterTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_endUnloadFilter");
	  camera.logevent_endUnloadFilter event = new camera.logevent_endUnloadFilter();
          System.out.println("Event endUnloadFilter logger ready ");

	  while (!finished) {
	     status = evt.getEvent_endUnloadFilter(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

