package camera;

public interface command_stopDataWriter extends
    camera.command_stopDataWriterOperations,
    DDS.DataWriter
{
}
