package camera;

public class logevent_endLoadFilterTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_endLoadFilterTypeSupport()
    {
        super("camera::logevent_endLoadFilter",
              "",
              "",
              null,
              camera.logevent_endLoadFilterMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_endLoadFilterDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_endLoadFilterDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_endLoadFilterDataReaderViewImpl(this);
    }
}
