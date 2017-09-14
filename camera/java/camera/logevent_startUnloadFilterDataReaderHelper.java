package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startUnloadFilterDataReaderHelper
{

    public static camera.logevent_startUnloadFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterDataReader) {
            return (camera.logevent_startUnloadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startUnloadFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterDataReader) {
            return (camera.logevent_startUnloadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
