package camera;

public final class Cryo {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public float[] Cold_temperature = new float[3];
    public float Compressor;
    public float[] Compressor_speed = new float[2];
    public float[] Cryo_temperature = new float[12];
    public float[] Discharge_pressure = new float[2];
    public float[] Discharge_temp = new float[2];
    public short[] Flow_interlock = new short[2];
    public float[] Heater_current = new float[6];
    public float[] Heater_voltage = new float[6];
    public float[] Intake_flow = new float[2];
    public float[] Intake_pressure = new float[2];
    public float[] Intake_temp = new float[2];
    public float[] Post_expansion_pressure = new float[2];
    public float[] Post_expansion_temp = new float[2];
    public float[] Pre_expansion_pressure = new float[2];
    public float[] Pre_expansion_temp = new float[2];
    public float[] Return_temp = new float[2];

    public Cryo() {
    }

    public Cryo(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        float[] _Cold_temperature,
        float _Compressor,
        float[] _Compressor_speed,
        float[] _Cryo_temperature,
        float[] _Discharge_pressure,
        float[] _Discharge_temp,
        short[] _Flow_interlock,
        float[] _Heater_current,
        float[] _Heater_voltage,
        float[] _Intake_flow,
        float[] _Intake_pressure,
        float[] _Intake_temp,
        float[] _Post_expansion_pressure,
        float[] _Post_expansion_temp,
        float[] _Pre_expansion_pressure,
        float[] _Pre_expansion_temp,
        float[] _Return_temp)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Cold_temperature = _Cold_temperature;
        Compressor = _Compressor;
        Compressor_speed = _Compressor_speed;
        Cryo_temperature = _Cryo_temperature;
        Discharge_pressure = _Discharge_pressure;
        Discharge_temp = _Discharge_temp;
        Flow_interlock = _Flow_interlock;
        Heater_current = _Heater_current;
        Heater_voltage = _Heater_voltage;
        Intake_flow = _Intake_flow;
        Intake_pressure = _Intake_pressure;
        Intake_temp = _Intake_temp;
        Post_expansion_pressure = _Post_expansion_pressure;
        Post_expansion_temp = _Post_expansion_temp;
        Pre_expansion_pressure = _Pre_expansion_pressure;
        Pre_expansion_temp = _Pre_expansion_temp;
        Return_temp = _Return_temp;
    }

}
