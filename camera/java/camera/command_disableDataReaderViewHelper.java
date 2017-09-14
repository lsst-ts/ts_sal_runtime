package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_disableDataReaderViewHelper
{

    public static camera.command_disableDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_disableDataReaderView) {
            return (camera.command_disableDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_disableDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_disableDataReaderView) {
            return (camera.command_disableDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
