package camera;

public interface ShutterDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            camera.Shutter instance_data);

    long register_instance_w_timestamp(
            camera.Shutter instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            camera.Shutter instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            camera.Shutter instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            camera.Shutter instance_data, 
            long handle);

    int write_w_timestamp(
            camera.Shutter instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            camera.Shutter instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            camera.Shutter instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            camera.Shutter instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            camera.Shutter instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            camera.ShutterHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.Shutter instance_data);

}
