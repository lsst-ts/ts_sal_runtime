
import camera.*;
import org.lsst.sal.SAL_camera;

public class cameraEventLogger_startRotateCarouselTest {

	public static void main(String[] args) {
	  int status   = SAL_camera.SAL__OK;
	  boolean finished=false;

	  // Initialize
	  SAL_camera evt = new SAL_camera();
          evt.salEvent("camera_logevent_startRotateCarousel");
	  camera.logevent_startRotateCarousel event = new camera.logevent_startRotateCarousel();
          System.out.println("Event startRotateCarousel logger ready ");

	  while (!finished) {
	     status = evt.getEvent_startRotateCarousel(event);
	     if (status == SAL_camera.SAL__OK) {
                System.out.println("=== Event Logged : " + event);
             }
 	     try {Thread.sleep(100);} catch (InterruptedException e)  { e.printStackTrace(); }
	  }

	  /* Remove the DataWriters etc */
	  evt.salShutdown();
       }
}

