package camera;

public class logevent_endTakeImageTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endTakeImageTypeSupport()
    {
        super("camera::logevent_endTakeImage",
              "",
              "",
              null,
              camera.logevent_endTakeImageMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endTakeImageDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endTakeImageDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endTakeImageDataReaderViewImpl(this);
    }
}