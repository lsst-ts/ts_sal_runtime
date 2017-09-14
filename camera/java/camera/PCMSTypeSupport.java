package camera;

public class PCMSTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public PCMSTypeSupport()
    {
        super("camera::PCMS",
              "",
              "",
              null,
              camera.PCMSMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new PCMSDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new PCMSDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new PCMSDataReaderViewImpl(this);
    }
}