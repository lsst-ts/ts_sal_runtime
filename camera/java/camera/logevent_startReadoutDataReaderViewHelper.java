package camera;

import org.opensplice.dds.dcps.Utilities;

public final class logevent_startReadoutDataReaderViewHelper
{

    public static camera.logevent_startReadoutDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startReadoutDataReaderView) {
            return (camera.logevent_startReadoutDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.logevent_startReadoutDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.logevent_startReadoutDataReaderView) {
            return (camera.logevent_startReadoutDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
