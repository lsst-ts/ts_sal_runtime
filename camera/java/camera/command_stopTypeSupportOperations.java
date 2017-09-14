package camera;

public interface command_stopTypeSupportOperations extends
    DDS.TypeSupportOperations
{
    @Override
    int register_type(
            DDS.DomainParticipant participant, 
            java.lang.String type_name);

}
