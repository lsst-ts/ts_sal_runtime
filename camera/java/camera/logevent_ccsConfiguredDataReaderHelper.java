package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ccsConfiguredDataReaderHelper
{

    public static camera.logevent_ccsConfiguredDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredDataReader) {
            return (camera.logevent_ccsConfiguredDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ccsConfiguredDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredDataReader) {
            return (camera.logevent_ccsConfiguredDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
