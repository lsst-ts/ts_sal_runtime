package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_readyToTakeImageDataReaderHelper
{

    public static camera.logevent_readyToTakeImageDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_readyToTakeImageDataReader) {
            return (camera.logevent_readyToTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_readyToTakeImageDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_readyToTakeImageDataReader) {
            return (camera.logevent_readyToTakeImageDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
