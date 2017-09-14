package camera;

public final class logevent {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_origin;
    public int private_host;
    public java.lang.String message = "";

    public logevent() {
    }

    public logevent(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_origin,
        int _private_host,
        java.lang.String _message)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_origin = _private_origin;
        private_host = _private_host;
        message = _message;
    }

}
