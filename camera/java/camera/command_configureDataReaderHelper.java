package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_configureDataReaderHelper
{

    public static camera.command_configureDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_configureDataReader) {
            return (camera.command_configureDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_configureDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_configureDataReader) {
            return (camera.command_configureDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}