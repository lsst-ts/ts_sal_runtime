package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_prepareToTakeImageDataReaderViewHelper
{

    public static camera.logevent_prepareToTakeImageDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageDataReaderView) {
            return (camera.logevent_prepareToTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_prepareToTakeImageDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageDataReaderView) {
            return (camera.logevent_prepareToTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
