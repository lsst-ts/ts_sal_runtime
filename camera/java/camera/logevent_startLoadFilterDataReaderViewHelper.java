package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startLoadFilterDataReaderViewHelper
{

    public static camera.logevent_startLoadFilterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterDataReaderView) {
            return (camera.logevent_startLoadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startLoadFilterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startLoadFilterDataReaderView) {
            return (camera.logevent_startLoadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
