package camera;

import org.opensplice.dds.dcps.Utilities;

public final class PurgeTypeSupportHelper
{

    public static camera.PurgeTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.PurgeTypeSupport) {
            return (camera.PurgeTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.PurgeTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.PurgeTypeSupport) {
            return (camera.PurgeTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
