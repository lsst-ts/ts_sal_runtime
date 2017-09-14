package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endRotateCarouselDataReaderViewHelper
{

    public static camera.logevent_endRotateCarouselDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselDataReaderView) {
            return (camera.logevent_endRotateCarouselDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endRotateCarouselDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselDataReaderView) {
            return (camera.logevent_endRotateCarouselDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
