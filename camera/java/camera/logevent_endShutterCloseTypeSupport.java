package camera;

public class logevent_endShutterCloseTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endShutterCloseTypeSupport()
    {
        super("camera::logevent_endShutterClose",
              "",
              "",
              null,
              camera.logevent_endShutterCloseMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endShutterCloseDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endShutterCloseDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endShutterCloseDataReaderViewImpl(this);
    }
}
