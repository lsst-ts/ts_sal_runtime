package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_prepareToTakeImageDataReaderHelper
{

    public static camera.logevent_prepareToTakeImageDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageDataReader) {
            return (camera.logevent_prepareToTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_prepareToTakeImageDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_prepareToTakeImageDataReader) {
            return (camera.logevent_prepareToTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
