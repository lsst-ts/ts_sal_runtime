package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ShutterDataReaderViewHelper
{

    public static camera.ShutterDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ShutterDataReaderView) {
            return (camera.ShutterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ShutterDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ShutterDataReaderView) {
            return (camera.ShutterDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
