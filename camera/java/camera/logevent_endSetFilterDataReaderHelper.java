package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endSetFilterDataReaderHelper
{

    public static camera.logevent_endSetFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endSetFilterDataReader) {
            return (camera.logevent_endSetFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endSetFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endSetFilterDataReader) {
            return (camera.logevent_endSetFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
