package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterCloseDataWriterHelper
{

    public static camera.logevent_endShutterCloseDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseDataWriter) {
            return (camera.logevent_endShutterCloseDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterCloseDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseDataWriter) {
            return (camera.logevent_endShutterCloseDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
