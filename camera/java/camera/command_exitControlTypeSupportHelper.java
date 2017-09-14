package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_exitControlTypeSupportHelper
{

    public static camera.command_exitControlTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_exitControlTypeSupport) {
            return (camera.command_exitControlTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_exitControlTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_exitControlTypeSupport) {
            return (camera.command_exitControlTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
