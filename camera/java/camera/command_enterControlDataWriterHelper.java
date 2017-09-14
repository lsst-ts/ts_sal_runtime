package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_enterControlDataWriterHelper
{

    public static camera.command_enterControlDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_enterControlDataWriter) {
            return (camera.command_enterControlDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_enterControlDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_enterControlDataWriter) {
            return (camera.command_enterControlDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
