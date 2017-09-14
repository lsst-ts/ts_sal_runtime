package camera;

public class logevent_endShutterOpenTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endShutterOpenTypeSupport()
    {
        super("camera::logevent_endShutterOpen",
              "",
              "",
              null,
              camera.logevent_endShutterOpenMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endShutterOpenDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endShutterOpenDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endShutterOpenDataReaderViewImpl(this);
    }
}
