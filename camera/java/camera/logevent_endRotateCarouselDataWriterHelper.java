package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endRotateCarouselDataWriterHelper
{

    public static camera.logevent_endRotateCarouselDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselDataWriter) {
            return (camera.logevent_endRotateCarouselDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endRotateCarouselDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselDataWriter) {
            return (camera.logevent_endRotateCarouselDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
