package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startUnloadFilterTypeSupportHelper
{

    public static camera.logevent_startUnloadFilterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterTypeSupport) {
            return (camera.logevent_startUnloadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startUnloadFilterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterTypeSupport) {
            return (camera.logevent_startUnloadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
