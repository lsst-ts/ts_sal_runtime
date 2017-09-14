package camera;

public interface SDSDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            camera.SDS instance_data);

    long register_instance_w_timestamp(
            camera.SDS instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            camera.SDS instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            camera.SDS instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            camera.SDS instance_data, 
            long handle);

    int write_w_timestamp(
            camera.SDS instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            camera.SDS instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            camera.SDS instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            camera.SDS instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            camera.SDS instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            camera.SDSHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.SDS instance_data);

}
