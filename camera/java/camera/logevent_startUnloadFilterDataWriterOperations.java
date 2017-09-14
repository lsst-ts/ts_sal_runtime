package camera;

public interface logevent_startUnloadFilterDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            camera.logevent_startUnloadFilter instance_data);

    long register_instance_w_timestamp(
            camera.logevent_startUnloadFilter instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            camera.logevent_startUnloadFilter instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            camera.logevent_startUnloadFilter instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            camera.logevent_startUnloadFilter instance_data, 
            long handle);

    int write_w_timestamp(
            camera.logevent_startUnloadFilter instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            camera.logevent_startUnloadFilter instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            camera.logevent_startUnloadFilter instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            camera.logevent_startUnloadFilter instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            camera.logevent_startUnloadFilter instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            camera.logevent_startUnloadFilterHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.logevent_startUnloadFilter instance_data);

}
