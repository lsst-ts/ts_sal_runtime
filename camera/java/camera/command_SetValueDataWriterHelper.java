package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_SetValueDataWriterHelper
{

    public static camera.command_SetValueDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueDataWriter) {
            return (camera.command_SetValueDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_SetValueDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueDataWriter) {
            return (camera.command_SetValueDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
