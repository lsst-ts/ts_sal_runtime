package camera;

public final class WAS {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public short Board_ID;
    public float[] Board_current = new float[4];
    public float[] Board_temp = new float[12];
    public float[] Board_voltage = new float[4];
    public int[] CABAC_MUX = new int[4];
    public short CCD_ID;
    public float CCD_temp;
    public int[] FPGACheckSum = new int[2];
    public short REB_ID;

    public WAS() {
    }

    public WAS(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        short _Board_ID,
        float[] _Board_current,
        float[] _Board_temp,
        float[] _Board_voltage,
        int[] _CABAC_MUX,
        short _CCD_ID,
        float _CCD_temp,
        int[] _FPGACheckSum,
        short _REB_ID)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        Board_ID = _Board_ID;
        Board_current = _Board_current;
        Board_temp = _Board_temp;
        Board_voltage = _Board_voltage;
        CABAC_MUX = _CABAC_MUX;
        CCD_ID = _CCD_ID;
        CCD_temp = _CCD_temp;
        FPGACheckSum = _FPGACheckSum;
        REB_ID = _REB_ID;
    }

}
