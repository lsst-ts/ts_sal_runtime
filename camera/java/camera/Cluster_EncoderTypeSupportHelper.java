package camera;

import org.opensplice.dds.dcps.Utilities;

public final class Cluster_EncoderTypeSupportHelper
{

    public static camera.Cluster_EncoderTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderTypeSupport) {
            return (camera.Cluster_EncoderTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.Cluster_EncoderTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderTypeSupport) {
            return (camera.Cluster_EncoderTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
