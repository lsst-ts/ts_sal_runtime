package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startRotateCarouselDataWriterHelper
{

    public static camera.logevent_startRotateCarouselDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselDataWriter) {
            return (camera.logevent_startRotateCarouselDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startRotateCarouselDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselDataWriter) {
            return (camera.logevent_startRotateCarouselDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
