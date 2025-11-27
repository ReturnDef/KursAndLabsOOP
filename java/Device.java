package smarthome;
public interface Device {
    String getId();
    String getName();
    String getLocation();
    void setName(String name);
    void setLocation(String location);
    void turnOn();
    void turnOff();
    boolean isOn();
    void perform(String command);

    int getPowerUsage();

}
