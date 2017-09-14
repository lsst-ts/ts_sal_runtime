package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startRotateCarouselDataReaderViewHelper
{

    public static camera.logevent_startRotateCarouselDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselDataReaderView) {
            return (camera.logevent_startRotateCarouselDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startRotateCarouselDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselDataReaderView) {
            return (camera.logevent_startRotateCarouselDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
