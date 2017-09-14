package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endUnloadFilterDataReaderViewHelper
{

    public static camera.logevent_endUnloadFilterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endUnloadFilterDataReaderView) {
            return (camera.logevent_endUnloadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endUnloadFilterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endUnloadFilterDataReaderView) {
            return (camera.logevent_endUnloadFilterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
