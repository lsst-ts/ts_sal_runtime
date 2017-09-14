package camera;

public class logevent_startSetFilterTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_startSetFilterTypeSupport()
    {
        super("camera::logevent_startSetFilter",
              "",
              "",
              null,
              camera.logevent_startSetFilterMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_startSetFilterDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_startSetFilterDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_startSetFilterDataReaderViewImpl(this);
    }
}
