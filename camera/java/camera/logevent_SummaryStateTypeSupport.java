package camera;

public class logevent_SummaryStateTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public logevent_SummaryStateTypeSupport()
    {
        super("camera::logevent_SummaryState",
              "",
              "",
              null,
              camera.logevent_SummaryStateMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new logevent_SummaryStateDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new logevent_SummaryStateDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new logevent_SummaryStateDataReaderViewImpl(this);
    }
}
