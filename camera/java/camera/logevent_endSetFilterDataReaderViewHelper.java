package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endSetFilterDataReaderViewHelper
{

    public static camera.logevent_endSetFilterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endSetFilterDataReaderView) {
            return (camera.logevent_endSetFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endSetFilterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endSetFilterDataReaderView) {
            return (camera.logevent_endSetFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
