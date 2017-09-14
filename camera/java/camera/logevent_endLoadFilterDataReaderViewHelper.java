package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endLoadFilterDataReaderViewHelper
{

    public static camera.logevent_endLoadFilterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterDataReaderView) {
            return (camera.logevent_endLoadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endLoadFilterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endLoadFilterDataReaderView) {
            return (camera.logevent_endLoadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
