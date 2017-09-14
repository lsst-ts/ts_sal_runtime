package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_enterControlTypeSupportHelper
{

    public static camera.command_enterControlTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_enterControlTypeSupport) {
            return (camera.command_enterControlTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_enterControlTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_enterControlTypeSupport) {
            return (camera.command_enterControlTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
