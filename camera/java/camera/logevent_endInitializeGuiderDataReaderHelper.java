package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endInitializeGuiderDataReaderHelper
{

    public static camera.logevent_endInitializeGuiderDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderDataReader) {
            return (camera.logevent_endInitializeGuiderDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endInitializeGuiderDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderDataReader) {
            return (camera.logevent_endInitializeGuiderDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
