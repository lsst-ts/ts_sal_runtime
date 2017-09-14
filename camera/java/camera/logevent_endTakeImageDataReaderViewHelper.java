package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endTakeImageDataReaderViewHelper
{

    public static camera.logevent_endTakeImageDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageDataReaderView) {
            return (camera.logevent_endTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endTakeImageDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageDataReaderView) {
            return (camera.logevent_endTakeImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
