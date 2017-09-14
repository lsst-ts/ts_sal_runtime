package camera;

public final class command_SetValueHolder
{

    public camera.command_SetValue value = null;

    public command_SetValueHolder () { }

    public command_SetValueHolder (camera.command_SetValue initialValue)
    {
        value = initialValue;
    }

}
