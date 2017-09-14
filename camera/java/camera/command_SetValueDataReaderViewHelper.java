package camera;

import org.opensplice.dds.dcps.Utilities;

public final class command_SetValueDataReaderViewHelper
{

    public static camera.command_SetValueDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueDataReaderView) {
            return (camera.command_SetValueDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.command_SetValueDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.command_SetValueDataReaderView) {
            return (camera.command_SetValueDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
