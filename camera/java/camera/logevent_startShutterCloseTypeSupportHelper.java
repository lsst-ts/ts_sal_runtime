package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterCloseTypeSupportHelper
{

    public static camera.logevent_startShutterCloseTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseTypeSupport) {
            return (camera.logevent_startShutterCloseTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterCloseTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseTypeSupport) {
            return (camera.logevent_startShutterCloseTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
