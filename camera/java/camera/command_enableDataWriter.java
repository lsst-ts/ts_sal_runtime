package camera;

public interface command_enableDataWriter extends
    camera.command_enableDataWriterOperations,
    DDS.DataWriter
{
}
