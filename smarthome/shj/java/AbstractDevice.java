package smarthome;

public abstract class AbstractDevice implements Device {

    protected String id;
    protected String name;
    protected String location;
    protected boolean isOn;
    protected int powerUsage;

    public AbstractDevice(String id, String name, String location, int powerUsage) {
        this.id = id;
        this.name = name;
        this.location = location;
        this.powerUsage = powerUsage;
        this.isOn = false;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getLocation() {
        return location;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public void turnOn() {
        isOn = true;
        System.out.println(name + " включено");
    }

    public void turnOff() {
        isOn = false;
        System.out.println(name + " выключено");
    }

    public boolean isOn() {
        return isOn;
    }

    public int getPowerUsage() {
        return powerUsage;
    }

    public String toString() {
        return id + ": " + name + " (" + location + ") " + (isOn ? "[вкл]" : "[выкл]");
    }

    public void perform(String command) {
        System.out.println(name + ": команда '" + command + "' не распознана");
    }
}
