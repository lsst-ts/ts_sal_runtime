package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startIntegrationDataWriterHelper
{

    public static camera.logevent_startIntegrationDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startIntegrationDataWriter) {
            return (camera.logevent_startIntegrationDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startIntegrationDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startIntegrationDataWriter) {
            return (camera.logevent_startIntegrationDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
