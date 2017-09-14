package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_AppliedSettingsMatchStartDataWriterHelper
{

    public static camera.logevent_AppliedSettingsMatchStartDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_AppliedSettingsMatchStartDataWriter) {
            return (camera.logevent_AppliedSettingsMatchStartDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_AppliedSettingsMatchStartDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_AppliedSettingsMatchStartDataWriter) {
            return (camera.logevent_AppliedSettingsMatchStartDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
