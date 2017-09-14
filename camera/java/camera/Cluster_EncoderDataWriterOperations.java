package camera;

public interface Cluster_EncoderDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            camera.Cluster_Encoder instance_data);

    long register_instance_w_timestamp(
            camera.Cluster_Encoder instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            camera.Cluster_Encoder instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            camera.Cluster_Encoder instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            camera.Cluster_Encoder instance_data, 
            long handle);

    int write_w_timestamp(
            camera.Cluster_Encoder instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            camera.Cluster_Encoder instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            camera.Cluster_Encoder instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            camera.Cluster_Encoder instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            camera.Cluster_Encoder instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            camera.Cluster_EncoderHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.Cluster_Encoder instance_data);

}
