package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endInitializeGuiderDataWriterHelper
{

    public static camera.logevent_endInitializeGuiderDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderDataWriter) {
            return (camera.logevent_endInitializeGuiderDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endInitializeGuiderDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderDataWriter) {
            return (camera.logevent_endInitializeGuiderDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
