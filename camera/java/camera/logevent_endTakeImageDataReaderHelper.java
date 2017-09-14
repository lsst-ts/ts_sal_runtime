package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endTakeImageDataReaderHelper
{

    public static camera.logevent_endTakeImageDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageDataReader) {
            return (camera.logevent_endTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endTakeImageDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endTakeImageDataReader) {
            return (camera.logevent_endTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
