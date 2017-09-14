package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_AppliedSettingsMatchStartTypeSupportHelper
{

    public static camera.logevent_AppliedSettingsMatchStartTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_AppliedSettingsMatchStartTypeSupport) {
            return (camera.logevent_AppliedSettingsMatchStartTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_AppliedSettingsMatchStartTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_AppliedSettingsMatchStartTypeSupport) {
            return (camera.logevent_AppliedSettingsMatchStartTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
