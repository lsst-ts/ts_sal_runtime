package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endInitializeImageTypeSupportHelper
{

    public static camera.logevent_endInitializeImageTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeImageTypeSupport) {
            return (camera.logevent_endInitializeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endInitializeImageTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeImageTypeSupport) {
            return (camera.logevent_endInitializeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
