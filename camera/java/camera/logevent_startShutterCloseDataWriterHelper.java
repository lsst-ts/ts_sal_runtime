package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterCloseDataWriterHelper
{

    public static camera.logevent_startShutterCloseDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseDataWriter) {
            return (camera.logevent_startShutterCloseDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterCloseDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseDataWriter) {
            return (camera.logevent_startShutterCloseDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
