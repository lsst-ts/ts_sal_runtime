package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startRotateCarouselTypeSupportHelper
{

    public static camera.logevent_startRotateCarouselTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselTypeSupport) {
            return (camera.logevent_startRotateCarouselTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startRotateCarouselTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startRotateCarouselTypeSupport) {
            return (camera.logevent_startRotateCarouselTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
