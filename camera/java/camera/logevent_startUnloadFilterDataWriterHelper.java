package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startUnloadFilterDataWriterHelper
{

    public static camera.logevent_startUnloadFilterDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterDataWriter) {
            return (camera.logevent_startUnloadFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startUnloadFilterDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterDataWriter) {
            return (camera.logevent_startUnloadFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
