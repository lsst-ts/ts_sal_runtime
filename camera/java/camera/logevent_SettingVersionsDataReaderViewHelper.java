package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SettingVersionsDataReaderViewHelper
{

    public static camera.logevent_SettingVersionsDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsDataReaderView) {
            return (camera.logevent_SettingVersionsDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SettingVersionsDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SettingVersionsDataReaderView) {
            return (camera.logevent_SettingVersionsDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
