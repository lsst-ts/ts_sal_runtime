package camera;

public class logevent_prepareToTakeImageTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_prepareToTakeImageTypeSupport()
    {
        super("camera::logevent_prepareToTakeImage",
              "",
              "",
              null,
              camera.logevent_prepareToTakeImageMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_prepareToTakeImageDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_prepareToTakeImageDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_prepareToTakeImageDataReaderViewImpl(this);
    }
}
