package camera;

public class logevent_ErrorCodeTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_ErrorCodeTypeSupport()
    {
        super("camera::logevent_ErrorCode",
              "",
              "",
              null,
              camera.logevent_ErrorCodeMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_ErrorCodeDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_ErrorCodeDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_ErrorCodeDataReaderViewImpl(this);
    }
}
