package camera;

public class logevent_startIntegrationTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_startIntegrationTypeSupport()
    {
        super("camera::logevent_startIntegration",
              "",
              "",
              null,
              camera.logevent_startIntegrationMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_startIntegrationDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_startIntegrationDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_startIntegrationDataReaderViewImpl(this);
    }
}
