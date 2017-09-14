package camera;

public final class SDS {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public short REB_ID;
    public int[] Timing_parameter = new int[10];
    public int[] flag = new int[20];

    public SDS() {
    }

    public SDS(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        short _REB_ID,
        int[] _Timing_parameter,
        int[] _flag)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        REB_ID = _REB_ID;
        Timing_parameter = _Timing_parameter;
        flag = _flag;
    }

}
