package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startLoadFilterTypeSupportHelper
{

    public static camera.logevent_startLoadFilterTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterTypeSupport) {
            return (camera.logevent_startLoadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startLoadFilterTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterTypeSupport) {
            return (camera.logevent_startLoadFilterTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
