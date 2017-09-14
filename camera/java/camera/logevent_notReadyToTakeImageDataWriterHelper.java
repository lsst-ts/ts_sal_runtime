package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_notReadyToTakeImageDataWriterHelper
{

    public static camera.logevent_notReadyToTakeImageDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageDataWriter) {
            return (camera.logevent_notReadyToTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_notReadyToTakeImageDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_notReadyToTakeImageDataWriter) {
            return (camera.logevent_notReadyToTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
