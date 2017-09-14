package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_SetValueTypeSupportHelper
{

    public static camera.command_SetValueTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueTypeSupport) {
            return (camera.command_SetValueTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_SetValueTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueTypeSupport) {
            return (camera.command_SetValueTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
