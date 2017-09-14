package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SettingVersionsDataWriterHelper
{

    public static camera.logevent_SettingVersionsDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsDataWriter) {
            return (camera.logevent_SettingVersionsDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SettingVersionsDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsDataWriter) {
            return (camera.logevent_SettingVersionsDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
