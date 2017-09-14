package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SummaryStateTypeSupportHelper
{

    public static camera.logevent_SummaryStateTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateTypeSupport) {
            return (camera.logevent_SummaryStateTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SummaryStateTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateTypeSupport) {
            return (camera.logevent_SummaryStateTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
