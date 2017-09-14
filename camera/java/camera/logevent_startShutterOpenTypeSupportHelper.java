package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterOpenTypeSupportHelper
{

    public static camera.logevent_startShutterOpenTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenTypeSupport) {
            return (camera.logevent_startShutterOpenTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterOpenTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenTypeSupport) {
            return (camera.logevent_startShutterOpenTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
