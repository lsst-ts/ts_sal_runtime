package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SettingVersionsTypeSupportHelper
{

    public static camera.logevent_SettingVersionsTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsTypeSupport) {
            return (camera.logevent_SettingVersionsTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SettingVersionsTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsTypeSupport) {
            return (camera.logevent_SettingVersionsTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
