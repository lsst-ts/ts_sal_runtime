package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_prepareToTakeImageDataWriterHelper
{

    public static camera.logevent_prepareToTakeImageDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageDataWriter) {
            return (camera.logevent_prepareToTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_prepareToTakeImageDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageDataWriter) {
            return (camera.logevent_prepareToTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
