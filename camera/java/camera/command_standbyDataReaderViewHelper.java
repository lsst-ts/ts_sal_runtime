package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_standbyDataReaderViewHelper
{

    public static camera.command_standbyDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_standbyDataReaderView) {
            return (camera.command_standbyDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_standbyDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_standbyDataReaderView) {
            return (camera.command_standbyDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
