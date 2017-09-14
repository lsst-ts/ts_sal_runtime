package camera;

public final class Cluster_Encoder {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public float[] Image_SD = new float[3216];
    public float[] Image_mean = new float[3216];
    public float[] Overscan_SD = new float[3216];
    public float[] Overscan_mean = new float[3216];
    public float[] PSF = new float[9648];

    public Cluster_Encoder() {
    }

    public Cluster_Encoder(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        float[] _Image_SD,
        float[] _Image_mean,
        float[] _Overscan_SD,
        float[] _Overscan_mean,
        float[] _PSF)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Image_SD = _Image_SD;
        Image_mean = _Image_mean;
        Overscan_SD = _Overscan_SD;
        Overscan_mean = _Overscan_mean;
        PSF = _PSF;
    }

}
