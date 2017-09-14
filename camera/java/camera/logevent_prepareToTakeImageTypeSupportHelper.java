package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_prepareToTakeImageTypeSupportHelper
{

    public static camera.logevent_prepareToTakeImageTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageTypeSupport) {
            return (camera.logevent_prepareToTakeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_prepareToTakeImageTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageTypeSupport) {
            return (camera.logevent_prepareToTakeImageTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
