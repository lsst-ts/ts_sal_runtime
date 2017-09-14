package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endLoadFilterTypeSupportHelper
{

    public static camera.logevent_endLoadFilterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterTypeSupport) {
            return (camera.logevent_endLoadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endLoadFilterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterTypeSupport) {
            return (camera.logevent_endLoadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
