package camera;

public class logevent_SettingVersionsTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_SettingVersionsTypeSupport()
    {
        super("camera::logevent_SettingVersions",
              "",
              "",
              null,
              camera.logevent_SettingVersionsMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_SettingVersionsDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_SettingVersionsDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_SettingVersionsDataReaderViewImpl(this);
    }
}
