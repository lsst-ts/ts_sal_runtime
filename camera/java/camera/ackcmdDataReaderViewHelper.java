package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ackcmdDataReaderViewHelper
{

    public static camera.ackcmdDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdDataReaderView) {
            return (camera.ackcmdDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ackcmdDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdDataReaderView) {
            return (camera.ackcmdDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
