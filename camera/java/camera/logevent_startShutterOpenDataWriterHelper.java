package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterOpenDataWriterHelper
{

    public static camera.logevent_startShutterOpenDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenDataWriter) {
            return (camera.logevent_startShutterOpenDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterOpenDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenDataWriter) {
            return (camera.logevent_startShutterOpenDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
