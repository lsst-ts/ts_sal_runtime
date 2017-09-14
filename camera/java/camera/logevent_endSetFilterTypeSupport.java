package camera;

public class logevent_endSetFilterTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endSetFilterTypeSupport()
    {
        super("camera::logevent_endSetFilter",
              "",
              "",
              null,
              camera.logevent_endSetFilterMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endSetFilterDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endSetFilterDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endSetFilterDataReaderViewImpl(this);
    }
}
