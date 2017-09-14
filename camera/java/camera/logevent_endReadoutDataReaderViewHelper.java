package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_endReadoutDataReaderViewHelper
{

    public static camera.logevent_endReadoutDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutDataReaderView) {
            return (camera.logevent_endReadoutDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_endReadoutDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_endReadoutDataReaderView) {
            return (camera.logevent_endReadoutDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
