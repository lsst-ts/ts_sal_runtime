package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endLoadFilterDataWriterHelper
{

    public static camera.logevent_endLoadFilterDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterDataWriter) {
            return (camera.logevent_endLoadFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endLoadFilterDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterDataWriter) {
            return (camera.logevent_endLoadFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
