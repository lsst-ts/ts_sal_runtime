package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endTakeImageDataWriterHelper
{

    public static camera.logevent_endTakeImageDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageDataWriter) {
            return (camera.logevent_endTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endTakeImageDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageDataWriter) {
            return (camera.logevent_endTakeImageDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
