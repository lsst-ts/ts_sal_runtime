package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_ccsConfiguredDataReaderViewHelper
{

    public static camera.logevent_ccsConfiguredDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredDataReaderView) {
            return (camera.logevent_ccsConfiguredDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_ccsConfiguredDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_ccsConfiguredDataReaderView) {
            return (camera.logevent_ccsConfiguredDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
