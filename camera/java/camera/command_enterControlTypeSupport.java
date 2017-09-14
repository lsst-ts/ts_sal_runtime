package camera;

public class command_enterControlTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public command_enterControlTypeSupport()
    {
        super("camera::command_enterControl",
              "",
              "",
              null,
              camera.command_enterControlMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new command_enterControlDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new command_enterControlDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new command_enterControlDataReaderViewImpl(this);
    }
}
