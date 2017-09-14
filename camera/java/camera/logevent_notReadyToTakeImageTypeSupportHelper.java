package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_notReadyToTakeImageTypeSupportHelper
{

    public static camera.logevent_notReadyToTakeImageTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageTypeSupport) {
            return (camera.logevent_notReadyToTakeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_notReadyToTakeImageTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageTypeSupport) {
            return (camera.logevent_notReadyToTakeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
