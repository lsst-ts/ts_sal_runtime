package camera;

public class logevent_notReadyToTakeImageTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_notReadyToTakeImageTypeSupport()
    {
        super("camera::logevent_notReadyToTakeImage",
              "",
              "",
              null,
              camera.logevent_notReadyToTakeImageMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_notReadyToTakeImageDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_notReadyToTakeImageDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_notReadyToTakeImageDataReaderViewImpl(this);
    }
}
