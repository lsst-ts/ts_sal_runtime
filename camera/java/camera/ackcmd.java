package camera;

public final class ackcmd {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_origin;
    public int private_host;
    public int private_seqNum;
    public int ack;
    public int error;
    public java.lang.String result = "";

    public ackcmd() {
    }

    public ackcmd(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_origin,
        int _private_host,
        int _private_seqNum,
        int _ack,
        int _error,
        java.lang.String _result)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_origin = _private_origin;
        private_host = _private_host;
        private_seqNum = _private_seqNum;
        ack = _ack;
        error = _error;
        result = _result;
    }

}
