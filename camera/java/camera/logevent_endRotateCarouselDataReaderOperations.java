package camera;

public interface logevent_endRotateCarouselDataReaderOperations extends
    DDS.DataReaderOperations
{

    int read(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            int sample_states, 
            int view_states, 
            int instance_states);

    int take(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            int sample_states, 
            int view_states, 
            int instance_states);

    int read_w_condition(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            DDS.ReadCondition a_condition);

    int take_w_condition(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            DDS.ReadCondition a_condition);

    int read_next_sample(
            camera.logevent_endRotateCarouselHolder received_data, 
            DDS.SampleInfoHolder sample_info);

    int take_next_sample(
            camera.logevent_endRotateCarouselHolder received_data, 
            DDS.SampleInfoHolder sample_info);

    int read_instance(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples,
            long a_handle, 
            int sample_states, 
            int view_states, 
            int instance_states);

    int take_instance(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            long a_handle, 
            int sample_states, 
            int view_states, 
            int instance_states);

    int read_next_instance(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            long a_handle, 
            int sample_states, 
            int view_states, 
            int instance_states);

    int take_next_instance(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            long a_handle, 
            int sample_states, 
            int view_states, 
            int instance_states);

    int read_next_instance_w_condition(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            long a_handle, 
            DDS.ReadCondition a_condition);

    int take_next_instance_w_condition(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq, 
            int max_samples, 
            long a_handle, 
            DDS.ReadCondition a_condition);

    int return_loan(
            camera.logevent_endRotateCarouselSeqHolder received_data, 
            DDS.SampleInfoSeqHolder info_seq);

    int get_key_value(
            camera.logevent_endRotateCarouselHolder key_holder, 
            long handle);
    
    long lookup_instance(
            camera.logevent_endRotateCarousel instance);

}
