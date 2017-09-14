package camera;

public interface command_startDataWriter extends
    camera.command_startDataWriterOperations,
    DDS.DataWriter
{
}
