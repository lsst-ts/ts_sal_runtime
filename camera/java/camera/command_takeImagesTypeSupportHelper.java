package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_takeImagesTypeSupportHelper
{

    public static camera.command_takeImagesTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_takeImagesTypeSupport) {
            return (camera.command_takeImagesTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_takeImagesTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_takeImagesTypeSupport) {
            return (camera.command_takeImagesTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
