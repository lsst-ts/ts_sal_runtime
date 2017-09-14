package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_setFilterDataReaderHelper
{

    public static camera.command_setFilterDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_setFilterDataReader) {
            return (camera.command_setFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_setFilterDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_setFilterDataReader) {
            return (camera.command_setFilterDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
