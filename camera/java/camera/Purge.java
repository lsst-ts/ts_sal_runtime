package camera;

public final class Purge {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public float[] Accelerometer = new float[6];
    public float Blower_setting;
    public float Blower_speed;
    public float Body_Flow_meter;
    public float Body_Temp;
    public float Heater_current;
    public float Heaters;
    public int Microphone;
    public float Trunk_Flow_meter;
    public float Trunk_Temp;
    public int Valve_setting;
    public int Valves;

    public Purge() {
    }

    public Purge(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        float[] _Accelerometer,
        float _Blower_setting,
        float _Blower_speed,
        float _Body_Flow_meter,
        float _Body_Temp,
        float _Heater_current,
        float _Heaters,
        int _Microphone,
        float _Trunk_Flow_meter,
        float _Trunk_Temp,
        int _Valve_setting,
        int _Valves)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Accelerometer = _Accelerometer;
        Blower_setting = _Blower_setting;
        Blower_speed = _Blower_speed;
        Body_Flow_meter = _Body_Flow_meter;
        Body_Temp = _Body_Temp;
        Heater_current = _Heater_current;
        Heaters = _Heaters;
        Microphone = _Microphone;
        Trunk_Flow_meter = _Trunk_Flow_meter;
        Trunk_Temp = _Trunk_Temp;
        Valve_setting = _Valve_setting;
        Valves = _Valves;
    }

}
