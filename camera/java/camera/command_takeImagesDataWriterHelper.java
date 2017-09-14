package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_takeImagesDataWriterHelper
{

    public static camera.command_takeImagesDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_takeImagesDataWriter) {
            return (camera.command_takeImagesDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_takeImagesDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_takeImagesDataWriter) {
            return (camera.command_takeImagesDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
