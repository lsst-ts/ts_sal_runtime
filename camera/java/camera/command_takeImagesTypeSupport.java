package camera;

public class command_takeImagesTypeSupport extends org.opensplice.dds.dcps.TypeSupportImpl implements DDS.TypeSupportOperations
{
    private long copyCache;

    public command_takeImagesTypeSupport()
    {
        super("camera::command_takeImages",
              "",
              "",
              null,
              camera.command_takeImagesMetaHolder.metaDescriptor);
    }

    @Override
    protected void finalize() throws Throwable
    {
        super.finalize();
    }

    @Override
    protected DDS.DataWriter create_datawriter ()
    {
        return new command_takeImagesDataWriterImpl(this);
    }

    @Override
    protected DDS.DataReader create_datareader ()
    {
        return new command_takeImagesDataReaderImpl(this);
    }

    @Override
    protected DDS.DataReaderView create_dataview ()
    {
        return new command_takeImagesDataReaderViewImpl(this);
    }
}
