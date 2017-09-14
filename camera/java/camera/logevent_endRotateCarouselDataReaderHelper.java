package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endRotateCarouselDataReaderHelper
{

    public static camera.logevent_endRotateCarouselDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselDataReader) {
            return (camera.logevent_endRotateCarouselDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endRotateCarouselDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselDataReader) {
            return (camera.logevent_endRotateCarouselDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
