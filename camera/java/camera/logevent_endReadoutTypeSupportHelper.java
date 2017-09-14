package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endReadoutTypeSupportHelper
{

    public static camera.logevent_endReadoutTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutTypeSupport) {
            return (camera.logevent_endReadoutTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endReadoutTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutTypeSupport) {
            return (camera.logevent_endReadoutTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
