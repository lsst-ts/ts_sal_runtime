package camera;

public class logevent_endRotateCarouselTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endRotateCarouselTypeSupport()
    {
        super("camera::logevent_endRotateCarousel",
              "",
              "",
              null,
              camera.logevent_endRotateCarouselMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endRotateCarouselDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endRotateCarouselDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endRotateCarouselDataReaderViewImpl(this);
    }
}
