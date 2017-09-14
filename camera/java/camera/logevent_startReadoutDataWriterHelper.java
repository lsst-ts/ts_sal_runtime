package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startReadoutDataWriterHelper
{

    public static camera.logevent_startReadoutDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startReadoutDataWriter) {
            return (camera.logevent_startReadoutDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startReadoutDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startReadoutDataWriter) {
            return (camera.logevent_startReadoutDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
