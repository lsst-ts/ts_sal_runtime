package camera;

public class logevent_startShutterOpenTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_startShutterOpenTypeSupport()
    {
        super("camera::logevent_startShutterOpen",
              "",
              "",
              null,
              camera.logevent_startShutterOpenMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_startShutterOpenDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_startShutterOpenDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_startShutterOpenDataReaderViewImpl(this);
    }
}
