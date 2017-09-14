package camera;

public class logevent_startShutterCloseTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_startShutterCloseTypeSupport()
    {
        super("camera::logevent_startShutterClose",
              "",
              "",
              null,
              camera.logevent_startShutterCloseMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_startShutterCloseDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_startShutterCloseDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_startShutterCloseDataReaderViewImpl(this);
    }
}
