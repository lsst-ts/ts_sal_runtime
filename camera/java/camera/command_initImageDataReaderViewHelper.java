package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_initImageDataReaderViewHelper
{

    public static camera.command_initImageDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initImageDataReaderView) {
            return (camera.command_initImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_initImageDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initImageDataReaderView) {
            return (camera.command_initImageDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
