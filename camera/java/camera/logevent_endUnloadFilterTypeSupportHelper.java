package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endUnloadFilterTypeSupportHelper
{

    public static camera.logevent_endUnloadFilterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endUnloadFilterTypeSupport) {
            return (camera.logevent_endUnloadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endUnloadFilterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endUnloadFilterTypeSupport) {
            return (camera.logevent_endUnloadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
