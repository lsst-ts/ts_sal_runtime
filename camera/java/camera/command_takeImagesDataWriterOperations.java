package camera;

public interface command_takeImagesDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            camera.command_takeImages instance_data);

    long register_instance_w_timestamp(
            camera.command_takeImages instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            camera.command_takeImages instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            camera.command_takeImages instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            camera.command_takeImages instance_data, 
            long handle);

    int write_w_timestamp(
            camera.command_takeImages instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            camera.command_takeImages instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            camera.command_takeImages instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            camera.command_takeImages instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            camera.command_takeImages instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            camera.command_takeImagesHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.command_takeImages instance_data);

}
