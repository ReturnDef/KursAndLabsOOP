package smarthome;

public class Sprinkler extends AbstractDevice {

    private int flowRate;

    public Sprinkler(String id, String name, String location, int powerUsage) {
        super(id, name, location, powerUsage);
    }

    public void setFlowRate(int f) {
        flowRate = f;
        System.out.println(name + ": поток " + flowRate);
    }

    public void perform(String command) {
        System.out.println(name + ": команда полива -> " + command);
    }
}
