package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endLoadFilterDataReaderHelper
{

    public static camera.logevent_endLoadFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterDataReader) {
            return (camera.logevent_endLoadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endLoadFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterDataReader) {
            return (camera.logevent_endLoadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
