package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SummaryStateDataWriterHelper
{

    public static camera.logevent_SummaryStateDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateDataWriter) {
            return (camera.logevent_SummaryStateDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SummaryStateDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateDataWriter) {
            return (camera.logevent_SummaryStateDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
