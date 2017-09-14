package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ccsConfiguredTypeSupportHelper
{

    public static camera.logevent_ccsConfiguredTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredTypeSupport) {
            return (camera.logevent_ccsConfiguredTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ccsConfiguredTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredTypeSupport) {
            return (camera.logevent_ccsConfiguredTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
