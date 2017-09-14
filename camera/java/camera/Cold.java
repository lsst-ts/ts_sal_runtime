package camera;

public final class Cold {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public float[] Compressor_load = new float[6];
    public float[] Compressor_speed = new float[6];
    public float[] Discharge_pressure = new float[6];
    public float[] Discharge_temp = new float[6];
    public short[] Flow_interlock = new short[6];
    public float[] Heater_current = new float[6];
    public float[] Heater_voltage = new float[6];
    public float[] Intake_flow = new float[6];
    public float[] Intake_pressure = new float[6];
    public float[] Intake_temp = new float[6];
    public float[] Ion_pump = new float[4];
    public short[] Mech_pump = new short[4];
    public float[] Post_expansion_pressure = new float[6];
    public float[] Post_expansion_temp = new float[6];
    public float[] Pre_expansion_pressure = new float[6];
    public float[] Pre_expansion_temp = new float[6];
    public int[] RGA = new int[10];
    public float[] Return_temp = new float[6];
    public float UtilityRoom_temperature;
    public float[] Vacuum_gauge = new float[5];
    public short[] Valve_status = new short[6];

    public Cold() {
    }

    public Cold(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        float[] _Compressor_load,
        float[] _Compressor_speed,
        float[] _Discharge_pressure,
        float[] _Discharge_temp,
        short[] _Flow_interlock,
        float[] _Heater_current,
        float[] _Heater_voltage,
        float[] _Intake_flow,
        float[] _Intake_pressure,
        float[] _Intake_temp,
        float[] _Ion_pump,
        short[] _Mech_pump,
        float[] _Post_expansion_pressure,
        float[] _Post_expansion_temp,
        float[] _Pre_expansion_pressure,
        float[] _Pre_expansion_temp,
        int[] _RGA,
        float[] _Return_temp,
        float _UtilityRoom_temperature,
        float[] _Vacuum_gauge,
        short[] _Valve_status)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Compressor_load = _Compressor_load;
        Compressor_speed = _Compressor_speed;
        Discharge_pressure = _Discharge_pressure;
        Discharge_temp = _Discharge_temp;
        Flow_interlock = _Flow_interlock;
        Heater_current = _Heater_current;
        Heater_voltage = _Heater_voltage;
        Intake_flow = _Intake_flow;
        Intake_pressure = _Intake_pressure;
        Intake_temp = _Intake_temp;
        Ion_pump = _Ion_pump;
        Mech_pump = _Mech_pump;
        Post_expansion_pressure = _Post_expansion_pressure;
        Post_expansion_temp = _Post_expansion_temp;
        Pre_expansion_pressure = _Pre_expansion_pressure;
        Pre_expansion_temp = _Pre_expansion_temp;
        RGA = _RGA;
        Return_temp = _Return_temp;
        UtilityRoom_temperature = _UtilityRoom_temperature;
        Vacuum_gauge = _Vacuum_gauge;
        Valve_status = _Valve_status;
    }

}
