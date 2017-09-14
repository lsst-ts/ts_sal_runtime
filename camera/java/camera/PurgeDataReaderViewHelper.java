package camera;

import org.opensplice.dds.dcps.Utilities;

public final class PurgeDataReaderViewHelper
{

    public static camera.PurgeDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.PurgeDataReaderView) {
            return (camera.PurgeDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.PurgeDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.PurgeDataReaderView) {
            return (camera.PurgeDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
