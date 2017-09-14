package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endReadoutDataReaderHelper
{

    public static camera.logevent_endReadoutDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutDataReader) {
            return (camera.logevent_endReadoutDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endReadoutDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutDataReader) {
            return (camera.logevent_endReadoutDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
