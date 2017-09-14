
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_endRotateCarouselTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_endRotateCarousel");
	  camera.logevent_endRotateCarousel event = new camera.logevent_endRotateCarousel();
          System.out.println("Event endRotateCarousel logger ready ");

	  while (!finished) {
	     status = evt.getEvent_endRotateCarousel(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

