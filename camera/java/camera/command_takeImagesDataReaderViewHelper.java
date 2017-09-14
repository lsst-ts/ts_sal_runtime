package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_takeImagesDataReaderViewHelper
{

    public static camera.command_takeImagesDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_takeImagesDataReaderView) {
            return (camera.command_takeImagesDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_takeImagesDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_takeImagesDataReaderView) {
            return (camera.command_takeImagesDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
