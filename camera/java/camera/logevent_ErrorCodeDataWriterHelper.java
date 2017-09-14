package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ErrorCodeDataWriterHelper
{

    public static camera.logevent_ErrorCodeDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeDataWriter) {
            return (camera.logevent_ErrorCodeDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ErrorCodeDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeDataWriter) {
            return (camera.logevent_ErrorCodeDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
