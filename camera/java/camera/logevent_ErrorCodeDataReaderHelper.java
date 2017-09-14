package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ErrorCodeDataReaderHelper
{

    public static camera.logevent_ErrorCodeDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeDataReader) {
            return (camera.logevent_ErrorCodeDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ErrorCodeDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeDataReader) {
            return (camera.logevent_ErrorCodeDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
