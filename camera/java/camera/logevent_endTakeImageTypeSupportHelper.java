package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endTakeImageTypeSupportHelper
{

    public static camera.logevent_endTakeImageTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageTypeSupport) {
            return (camera.logevent_endTakeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endTakeImageTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageTypeSupport) {
            return (camera.logevent_endTakeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
