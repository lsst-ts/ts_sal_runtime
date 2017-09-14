package camera;

public class logevent_endInitializeGuiderTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endInitializeGuiderTypeSupport()
    {
        super("camera::logevent_endInitializeGuider",
              "",
              "",
              null,
              camera.logevent_endInitializeGuiderMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endInitializeGuiderDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endInitializeGuiderDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endInitializeGuiderDataReaderViewImpl(this);
    }
}
