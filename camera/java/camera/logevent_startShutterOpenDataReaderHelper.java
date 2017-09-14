package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterOpenDataReaderHelper
{

    public static camera.logevent_startShutterOpenDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenDataReader) {
            return (camera.logevent_startShutterOpenDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterOpenDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenDataReader) {
            return (camera.logevent_startShutterOpenDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
