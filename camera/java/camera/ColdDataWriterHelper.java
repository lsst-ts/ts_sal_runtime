package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ColdDataWriterHelper
{

    public static camera.ColdDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ColdDataWriter) {
            return (camera.ColdDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ColdDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ColdDataWriter) {
            return (camera.ColdDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
