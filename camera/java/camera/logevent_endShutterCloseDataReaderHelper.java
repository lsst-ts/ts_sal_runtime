package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterCloseDataReaderHelper
{

    public static camera.logevent_endShutterCloseDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseDataReader) {
            return (camera.logevent_endShutterCloseDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterCloseDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseDataReader) {
            return (camera.logevent_endShutterCloseDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
