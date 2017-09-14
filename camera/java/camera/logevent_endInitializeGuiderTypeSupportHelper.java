package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endInitializeGuiderTypeSupportHelper
{

    public static camera.logevent_endInitializeGuiderTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderTypeSupport) {
            return (camera.logevent_endInitializeGuiderTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endInitializeGuiderTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderTypeSupport) {
            return (camera.logevent_endInitializeGuiderTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
