package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endSetFilterDataWriterHelper
{

    public static camera.logevent_endSetFilterDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endSetFilterDataWriter) {
            return (camera.logevent_endSetFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endSetFilterDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endSetFilterDataWriter) {
            return (camera.logevent_endSetFilterDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
