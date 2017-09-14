package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_setFilterTypeSupportHelper
{

    public static camera.command_setFilterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_setFilterTypeSupport) {
            return (camera.command_setFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_setFilterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_setFilterTypeSupport) {
            return (camera.command_setFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
