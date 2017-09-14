package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startRotateCarouselDataReaderHelper
{

    public static camera.logevent_startRotateCarouselDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselDataReader) {
            return (camera.logevent_startRotateCarouselDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startRotateCarouselDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselDataReader) {
            return (camera.logevent_startRotateCarouselDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
