package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SummaryStateDataReaderHelper
{

    public static camera.logevent_SummaryStateDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateDataReader) {
            return (camera.logevent_SummaryStateDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SummaryStateDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateDataReader) {
            return (camera.logevent_SummaryStateDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
