package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_notReadyToTakeImageDataReaderHelper
{

    public static camera.logevent_notReadyToTakeImageDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageDataReader) {
            return (camera.logevent_notReadyToTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_notReadyToTakeImageDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageDataReader) {
            return (camera.logevent_notReadyToTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
