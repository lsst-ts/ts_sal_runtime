package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterCloseTypeSupportHelper
{

    public static camera.logevent_endShutterCloseTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseTypeSupport) {
            return (camera.logevent_endShutterCloseTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterCloseTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseTypeSupport) {
            return (camera.logevent_endShutterCloseTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
