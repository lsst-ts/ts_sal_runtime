package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_exitControlDataReaderHelper
{

    public static camera.command_exitControlDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_exitControlDataReader) {
            return (camera.command_exitControlDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_exitControlDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_exitControlDataReader) {
            return (camera.command_exitControlDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
