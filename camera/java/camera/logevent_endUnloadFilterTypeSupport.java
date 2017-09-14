package camera;

public class logevent_endUnloadFilterTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endUnloadFilterTypeSupport()
    {
        super("camera::logevent_endUnloadFilter",
              "",
              "",
              null,
              camera.logevent_endUnloadFilterMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endUnloadFilterDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endUnloadFilterDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endUnloadFilterDataReaderViewImpl(this);
    }
}
