package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endShutterCloseDataReaderViewHelper
{

    public static camera.logevent_endShutterCloseDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseDataReaderView) {
            return (camera.logevent_endShutterCloseDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endShutterCloseDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endShutterCloseDataReaderView) {
            return (camera.logevent_endShutterCloseDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
