package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterOpenDataReaderHelper
{

    public static camera.logevent_endShutterOpenDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterOpenDataReader) {
            return (camera.logevent_endShutterOpenDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterOpenDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterOpenDataReader) {
            return (camera.logevent_endShutterOpenDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
