package camera;

public final class logevent_SettingVersions {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public java.lang.String recommendedSettingVersion = "";
    public int priority;

    public logevent_SettingVersions() {
    }

    public logevent_SettingVersions(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        java.lang.String _recommendedSettingVersion,
        int _priority)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        recommendedSettingVersion = _recommendedSettingVersion;
        priority = _priority;
    }

}
