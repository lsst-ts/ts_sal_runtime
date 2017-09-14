package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_SetValueDataReaderHelper
{

    public static camera.command_SetValueDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueDataReader) {
            return (camera.command_SetValueDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_SetValueDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueDataReader) {
            return (camera.command_SetValueDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
