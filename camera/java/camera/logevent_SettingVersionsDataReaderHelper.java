package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SettingVersionsDataReaderHelper
{

    public static camera.logevent_SettingVersionsDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsDataReader) {
            return (camera.logevent_SettingVersionsDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SettingVersionsDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsDataReader) {
            return (camera.logevent_SettingVersionsDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
