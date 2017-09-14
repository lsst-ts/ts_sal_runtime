package camera;

import org.opensplice.dds.dcps.Utilities;

public final class Cluster_EncoderDataReaderHelper
{

    public static camera.Cluster_EncoderDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderDataReader) {
            return (camera.Cluster_EncoderDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.Cluster_EncoderDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderDataReader) {
            return (camera.Cluster_EncoderDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
