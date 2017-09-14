package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endRotateCarouselTypeSupportHelper
{

    public static camera.logevent_endRotateCarouselTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselTypeSupport) {
            return (camera.logevent_endRotateCarouselTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endRotateCarouselTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endRotateCarouselTypeSupport) {
            return (camera.logevent_endRotateCarouselTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
