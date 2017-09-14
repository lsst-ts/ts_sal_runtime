package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endReadoutDataWriterHelper
{

    public static camera.logevent_endReadoutDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutDataWriter) {
            return (camera.logevent_endReadoutDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endReadoutDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutDataWriter) {
            return (camera.logevent_endReadoutDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
