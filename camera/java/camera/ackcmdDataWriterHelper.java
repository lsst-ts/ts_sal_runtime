package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ackcmdDataWriterHelper
{

    public static camera.ackcmdDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdDataWriter) {
            return (camera.ackcmdDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ackcmdDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdDataWriter) {
            return (camera.ackcmdDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
