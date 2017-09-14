package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterOpenDataReaderViewHelper
{

    public static camera.logevent_startShutterOpenDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenDataReaderView) {
            return (camera.logevent_startShutterOpenDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterOpenDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterOpenDataReaderView) {
            return (camera.logevent_startShutterOpenDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
