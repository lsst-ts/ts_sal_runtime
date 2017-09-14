package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ccsConfiguredDataWriterHelper
{

    public static camera.logevent_ccsConfiguredDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredDataWriter) {
            return (camera.logevent_ccsConfiguredDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ccsConfiguredDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredDataWriter) {
            return (camera.logevent_ccsConfiguredDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
