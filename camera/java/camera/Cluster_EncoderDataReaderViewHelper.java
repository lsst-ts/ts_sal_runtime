package camera;

import org.opensplice.dds.dcps.Utilities;

public final class Cluster_EncoderDataReaderViewHelper
{

    public static camera.Cluster_EncoderDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderDataReaderView) {
            return (camera.Cluster_EncoderDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static camera.Cluster_EncoderDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof camera.Cluster_EncoderDataReaderView) {
            return (camera.Cluster_EncoderDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
