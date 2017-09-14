package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterOpenTypeSupportHelper
{

    public static camera.logevent_endShutterOpenTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterOpenTypeSupport) {
            return (camera.logevent_endShutterOpenTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterOpenTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterOpenTypeSupport) {
            return (camera.logevent_endShutterOpenTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
