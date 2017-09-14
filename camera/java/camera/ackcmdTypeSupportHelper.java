package camera;

import org.opensplice.dds.dcps.Utilities;

public final class ackcmdTypeSupportHelper
{

    public static camera.ackcmdTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdTypeSupport) {
            return (camera.ackcmdTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.ackcmdTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.ackcmdTypeSupport) {
            return (camera.ackcmdTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
