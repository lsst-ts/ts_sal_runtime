package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_initGuidersDataReaderViewHelper
{

    public static camera.command_initGuidersDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersDataReaderView) {
            return (camera.command_initGuidersDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_initGuidersDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersDataReaderView) {
            return (camera.command_initGuidersDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
