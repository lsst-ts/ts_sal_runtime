package camera;

public final class command_stop {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public java.lang.String device = "";
    public java.lang.String property = "";
    public java.lang.String action = "";
    public java.lang.String value = "";
    public boolean state;

    public command_stop() {
    }

    public command_stop(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        java.lang.String _device,
        java.lang.String _property,
        java.lang.String _action,
        java.lang.String _value,
        boolean _state)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        device = _device;
        property = _property;
        action = _action;
        value = _value;
        state = _state;
    }

}
