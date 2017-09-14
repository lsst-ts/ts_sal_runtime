package camera;

public class logevent_startRotateCarouselTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_startRotateCarouselTypeSupport()
    {
        super("camera::logevent_startRotateCarousel",
              "",
              "",
              null,
              camera.logevent_startRotateCarouselMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_startRotateCarouselDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_startRotateCarouselDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_startRotateCarouselDataReaderViewImpl(this);
    }
}
