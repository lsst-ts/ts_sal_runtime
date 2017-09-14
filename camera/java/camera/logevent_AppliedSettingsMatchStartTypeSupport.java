package camera;

public class logevent_AppliedSettingsMatchStartTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_AppliedSettingsMatchStartTypeSupport()
    {
        super("camera::logevent_AppliedSettingsMatchStart",
              "",
              "",
              null,
              camera.logevent_AppliedSettingsMatchStartMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_AppliedSettingsMatchStartDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_AppliedSettingsMatchStartDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_AppliedSettingsMatchStartDataReaderViewImpl(this);
    }
}
