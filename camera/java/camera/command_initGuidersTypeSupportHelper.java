package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_initGuidersTypeSupportHelper
{

    public static camera.command_initGuidersTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersTypeSupport) {
            return (camera.command_initGuidersTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_initGuidersTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersTypeSupport) {
            return (camera.command_initGuidersTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
