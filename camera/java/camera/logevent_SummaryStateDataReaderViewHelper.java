package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_SummaryStateDataReaderViewHelper
{

    public static camera.logevent_SummaryStateDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateDataReaderView) {
            return (camera.logevent_SummaryStateDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_SummaryStateDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_SummaryStateDataReaderView) {
            return (camera.logevent_SummaryStateDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
