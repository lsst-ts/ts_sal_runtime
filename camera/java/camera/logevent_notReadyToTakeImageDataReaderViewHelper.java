package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_notReadyToTakeImageDataReaderViewHelper
{

    public static camera.logevent_notReadyToTakeImageDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageDataReaderView) {
            return (camera.logevent_notReadyToTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_notReadyToTakeImageDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageDataReaderView) {
            return (camera.logevent_notReadyToTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
