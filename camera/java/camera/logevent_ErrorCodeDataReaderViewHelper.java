package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ErrorCodeDataReaderViewHelper
{

    public static camera.logevent_ErrorCodeDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeDataReaderView) {
            return (camera.logevent_ErrorCodeDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ErrorCodeDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ErrorCodeDataReaderView) {
            return (camera.logevent_ErrorCodeDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
