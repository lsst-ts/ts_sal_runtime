package camera;

public final class Shutter {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public short[] Blade_home = new short[2];
    public float[] Close_profile = new float[24];
    public float[] Motor_current = new float[2];
    public float[] Motor_temp = new float[2];
    public short Open_direction;
    public float[] Open_profile = new float[24];
    public java.lang.String Profile_function = "";

    public Shutter() {
    }

    public Shutter(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        short[] _Blade_home,
        float[] _Close_profile,
        float[] _Motor_current,
        float[] _Motor_temp,
        short _Open_direction,
        float[] _Open_profile,
        java.lang.String _Profile_function)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Blade_home = _Blade_home;
        Close_profile = _Close_profile;
        Motor_current = _Motor_current;
        Motor_temp = _Motor_temp;
        Open_direction = _Open_direction;
        Open_profile = _Open_profile;
        Profile_function = _Profile_function;
    }

}
