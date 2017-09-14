package camera;

public class logevent_startUnloadFilterTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_startUnloadFilterTypeSupport()
    {
        super("camera::logevent_startUnloadFilter",
              "",
              "",
              null,
              camera.logevent_startUnloadFilterMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_startUnloadFilterDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_startUnloadFilterDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_startUnloadFilterDataReaderViewImpl(this);
    }
}
