package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startReadoutTypeSupportHelper
{

    public static camera.logevent_startReadoutTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startReadoutTypeSupport) {
            return (camera.logevent_startReadoutTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startReadoutTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startReadoutTypeSupport) {
            return (camera.logevent_startReadoutTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
