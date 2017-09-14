package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startSetFilterTypeSupportHelper
{

    public static camera.logevent_startSetFilterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterTypeSupport) {
            return (camera.logevent_startSetFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startSetFilterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterTypeSupport) {
            return (camera.logevent_startSetFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
