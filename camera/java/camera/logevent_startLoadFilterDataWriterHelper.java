package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startLoadFilterDataWriterHelper
{

    public static camera.logevent_startLoadFilterDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterDataWriter) {
            return (camera.logevent_startLoadFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startLoadFilterDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterDataWriter) {
            return (camera.logevent_startLoadFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
