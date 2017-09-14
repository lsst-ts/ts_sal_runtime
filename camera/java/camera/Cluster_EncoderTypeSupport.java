package camera;

public class Cluster_EncoderTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public Cluster_EncoderTypeSupport()
    {
        super("camera::Cluster_Encoder",
              "",
              "",
              null,
              camera.Cluster_EncoderMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new Cluster_EncoderDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new Cluster_EncoderDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new Cluster_EncoderDataReaderViewImpl(this);
    }
}
