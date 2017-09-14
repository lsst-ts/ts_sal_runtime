package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endInitializeGuiderDataReaderViewHelper
{

    public static camera.logevent_endInitializeGuiderDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderDataReaderView) {
            return (camera.logevent_endInitializeGuiderDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endInitializeGuiderDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeGuiderDataReaderView) {
            return (camera.logevent_endInitializeGuiderDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
