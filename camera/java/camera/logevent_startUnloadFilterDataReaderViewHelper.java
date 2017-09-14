package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startUnloadFilterDataReaderViewHelper
{

    public static camera.logevent_startUnloadFilterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterDataReaderView) {
            return (camera.logevent_startUnloadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startUnloadFilterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startUnloadFilterDataReaderView) {
            return (camera.logevent_startUnloadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
