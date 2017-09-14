package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_enterControlDataReaderViewHelper
{

    public static camera.command_enterControlDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_enterControlDataReaderView) {
            return (camera.command_enterControlDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_enterControlDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_enterControlDataReaderView) {
            return (camera.command_enterControlDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
