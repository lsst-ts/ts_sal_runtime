package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startLoadFilterDataReaderHelper
{

    public static camera.logevent_startLoadFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterDataReader) {
            return (camera.logevent_startLoadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startLoadFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterDataReader) {
            return (camera.logevent_startLoadFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
