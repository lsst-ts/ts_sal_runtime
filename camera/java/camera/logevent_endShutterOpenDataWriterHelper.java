package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterOpenDataWriterHelper
{

    public static camera.logevent_endShutterOpenDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterOpenDataWriter) {
            return (camera.logevent_endShutterOpenDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterOpenDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterOpenDataWriter) {
            return (camera.logevent_endShutterOpenDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
