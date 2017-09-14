package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_initGuidersDataReaderHelper
{

    public static camera.command_initGuidersDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersDataReader) {
            return (camera.command_initGuidersDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_initGuidersDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_initGuidersDataReader) {
            return (camera.command_initGuidersDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
