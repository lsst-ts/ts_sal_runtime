package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startShutterCloseDataReaderViewHelper
{

    public static camera.logevent_startShutterCloseDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseDataReaderView) {
            return (camera.logevent_startShutterCloseDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startShutterCloseDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startShutterCloseDataReaderView) {
            return (camera.logevent_startShutterCloseDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
