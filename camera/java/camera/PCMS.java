package camera;

public final class PCMS {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public short Bias_Status;
    public float Bias_current;
    public float Bias_voltage;
    public short Clock_Status;
    public float Clock_current;
    public float Clock_voltage;
    public short FPGA_Status;
    public float FPGA_current;
    public float FPGA_voltage;
    public short Low_Status;
    public float Low_current;
    public float Low_voltage;
    public short OD_Status;
    public float OD_current;
    public float OD_voltage;
    public short REB_ID;

    public PCMS() {
    }

    public PCMS(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        short _Bias_Status,
        float _Bias_current,
        float _Bias_voltage,
        short _Clock_Status,
        float _Clock_current,
        float _Clock_voltage,
        short _FPGA_Status,
        float _FPGA_current,
        float _FPGA_voltage,
        short _Low_Status,
        float _Low_current,
        float _Low_voltage,
        short _OD_Status,
        float _OD_current,
        float _OD_voltage,
        short _REB_ID)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Bias_Status = _Bias_Status;
        Bias_current = _Bias_current;
        Bias_voltage = _Bias_voltage;
        Clock_Status = _Clock_Status;
        Clock_current = _Clock_current;
        Clock_voltage = _Clock_voltage;
        FPGA_Status = _FPGA_Status;
        FPGA_current = _FPGA_current;
        FPGA_voltage = _FPGA_voltage;
        Low_Status = _Low_Status;
        Low_current = _Low_current;
        Low_voltage = _Low_voltage;
        OD_Status = _OD_Status;
        OD_current = _OD_current;
        OD_voltage = _OD_voltage;
        REB_ID = _REB_ID;
    }

}
