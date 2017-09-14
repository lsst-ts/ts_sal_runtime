package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startSetFilterDataWriterHelper
{

    public static camera.logevent_startSetFilterDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterDataWriter) {
            return (camera.logevent_startSetFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startSetFilterDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterDataWriter) {
            return (camera.logevent_startSetFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
