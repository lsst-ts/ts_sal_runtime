package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_exitControlDataReaderViewHelper
{

    public static camera.command_exitControlDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_exitControlDataReaderView) {
            return (camera.command_exitControlDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_exitControlDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_exitControlDataReaderView) {
            return (camera.command_exitControlDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
