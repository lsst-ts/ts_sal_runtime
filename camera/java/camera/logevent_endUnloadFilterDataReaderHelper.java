package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endUnloadFilterDataReaderHelper
{

    public static camera.logevent_endUnloadFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endUnloadFilterDataReader) {
            return (camera.logevent_endUnloadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endUnloadFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endUnloadFilterDataReader) {
            return (camera.logevent_endUnloadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
