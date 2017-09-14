package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ackcmdDataReaderHelper
{

    public static camera.ackcmdDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdDataReader) {
            return (camera.ackcmdDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ackcmdDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdDataReader) {
            return (camera.ackcmdDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
