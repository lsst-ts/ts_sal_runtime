package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startIntegrationDataReaderHelper
{

    public static camera.logevent_startIntegrationDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startIntegrationDataReader) {
            return (camera.logevent_startIntegrationDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startIntegrationDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startIntegrationDataReader) {
            return (camera.logevent_startIntegrationDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
