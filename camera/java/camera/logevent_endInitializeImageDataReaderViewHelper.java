package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endInitializeImageDataReaderViewHelper
{

    public static camera.logevent_endInitializeImageDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeImageDataReaderView) {
            return (camera.logevent_endInitializeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endInitializeImageDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endInitializeImageDataReaderView) {
            return (camera.logevent_endInitializeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
