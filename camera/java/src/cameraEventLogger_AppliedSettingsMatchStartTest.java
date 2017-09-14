
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_AppliedSettingsMatchStartTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_AppliedSettingsMatchStart");
	  camera.logevent_AppliedSettingsMatchStart event = new camera.logevent_AppliedSettingsMatchStart();
          System.out.println("Event AppliedSettingsMatchStart logger ready ");

	  while (!finished) {
	     status = evt.getEvent_AppliedSettingsMatchStart(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

