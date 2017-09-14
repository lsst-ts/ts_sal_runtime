package camera;

public interface ackcmdDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            camera.ackcmd instance_data);

    long register_instance_w_timestamp(
            camera.ackcmd instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            camera.ackcmd instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            camera.ackcmd instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            camera.ackcmd instance_data, 
            long handle);

    int write_w_timestamp(
            camera.ackcmd instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            camera.ackcmd instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            camera.ackcmd instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            camera.ackcmd instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            camera.ackcmd instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            camera.ackcmdHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.ackcmd instance_data);

}
