package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ShutterTypeSupportHelper
{

    public static camera.ShutterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ShutterTypeSupport) {
            return (camera.ShutterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ShutterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ShutterTypeSupport) {
            return (camera.ShutterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
