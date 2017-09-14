package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startSetFilterDataReaderViewHelper
{

    public static camera.logevent_startSetFilterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterDataReaderView) {
            return (camera.logevent_startSetFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startSetFilterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startSetFilterDataReaderView) {
            return (camera.logevent_startSetFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
