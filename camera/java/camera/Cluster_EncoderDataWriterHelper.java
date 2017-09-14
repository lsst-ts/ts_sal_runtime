package camera;

import org.opensplice.dds.dcps.Utilities;

public final class Cluster_EncoderDataWriterHelper
{

    public static camera.Cluster_EncoderDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderDataWriter) {
            return (camera.Cluster_EncoderDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.Cluster_EncoderDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderDataWriter) {
            return (camera.Cluster_EncoderDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
