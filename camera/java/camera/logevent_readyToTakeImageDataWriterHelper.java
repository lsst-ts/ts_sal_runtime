package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_readyToTakeImageDataWriterHelper
{

    public static camera.logevent_readyToTakeImageDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_readyToTakeImageDataWriter) {
            return (camera.logevent_readyToTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_readyToTakeImageDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_readyToTakeImageDataWriter) {
            return (camera.logevent_readyToTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
