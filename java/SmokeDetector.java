package smarthome;

public class SmokeDetector extends AbstractDevice {

    private double smokeLevel;

    public SmokeDetector(String id, String name, String location, int powerUsage) {
        super(id, name, location, powerUsage);
        smokeLevel = 0.0;
    }

    public void setSmokeLevel(double v) {
        smokeLevel = v;
        if (smokeLevel > 0.5) {
            System.out.println(name + ": обнаружен дым!");
        } else {
            System.out.println(name + ": уровень дыма " + smokeLevel);
        }
    }

    public void perform(String command) {
        if (command.toLowerCase().contains("провер")) {
            setSmokeLevel(Math.random());
        } else {
            System.out.println(name + ": неизвестная команда");
        }
    }

    @Override
    public String toString() {
        return super.toString() + " smoke=" + smokeLevel;
    }
}
