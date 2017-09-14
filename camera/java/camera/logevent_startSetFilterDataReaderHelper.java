package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startSetFilterDataReaderHelper
{

    public static camera.logevent_startSetFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterDataReader) {
            return (camera.logevent_startSetFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startSetFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterDataReader) {
            return (camera.logevent_startSetFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
