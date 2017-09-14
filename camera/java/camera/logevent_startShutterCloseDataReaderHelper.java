package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterCloseDataReaderHelper
{

    public static camera.logevent_startShutterCloseDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseDataReader) {
            return (camera.logevent_startShutterCloseDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterCloseDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseDataReader) {
            return (camera.logevent_startShutterCloseDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
