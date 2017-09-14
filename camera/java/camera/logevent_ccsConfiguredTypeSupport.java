package camera;

public class logevent_ccsConfiguredTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_ccsConfiguredTypeSupport()
    {
        super("camera::logevent_ccsConfigured",
              "",
              "",
              null,
              camera.logevent_ccsConfiguredMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_ccsConfiguredDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_ccsConfiguredDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_ccsConfiguredDataReaderViewImpl(this);
    }
}
