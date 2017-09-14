package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_initGuidersDataWriterHelper
{

    public static camera.command_initGuidersDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersDataWriter) {
            return (camera.command_initGuidersDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_initGuidersDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersDataWriter) {
            return (camera.command_initGuidersDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
