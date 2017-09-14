package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ErrorCodeTypeSupportHelper
{

    public static camera.logevent_ErrorCodeTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeTypeSupport) {
            return (camera.logevent_ErrorCodeTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ErrorCodeTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeTypeSupport) {
            return (camera.logevent_ErrorCodeTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
