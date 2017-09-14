package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_AppliedSettingsMatchStartDataReaderViewHelper
{

    public static camera.logevent_AppliedSettingsMatchStartDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_AppliedSettingsMatchStartDataReaderView) {
            return (camera.logevent_AppliedSettingsMatchStartDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_AppliedSettingsMatchStartDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_AppliedSettingsMatchStartDataReaderView) {
            return (camera.logevent_AppliedSettingsMatchStartDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
