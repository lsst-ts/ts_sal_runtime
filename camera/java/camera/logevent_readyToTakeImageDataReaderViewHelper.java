package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_readyToTakeImageDataReaderViewHelper
{

    public static camera.logevent_readyToTakeImageDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_readyToTakeImageDataReaderView) {
            return (camera.logevent_readyToTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_readyToTakeImageDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_readyToTakeImageDataReaderView) {
            return (camera.logevent_readyToTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
