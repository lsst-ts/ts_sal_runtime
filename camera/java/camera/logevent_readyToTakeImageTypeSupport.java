package camera;

public class logevent_readyToTakeImageTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_readyToTakeImageTypeSupport()
    {
        super("camera::logevent_readyToTakeImage",
              "",
              "",
              null,
              camera.logevent_readyToTakeImageMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_readyToTakeImageDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_readyToTakeImageDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_readyToTakeImageDataReaderViewImpl(this);
    }
}
