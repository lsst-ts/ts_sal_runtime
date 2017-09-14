package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startIntegrationTypeSupportHelper
{

    public static camera.logevent_startIntegrationTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startIntegrationTypeSupport) {
            return (camera.logevent_startIntegrationTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startIntegrationTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startIntegrationTypeSupport) {
            return (camera.logevent_startIntegrationTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
