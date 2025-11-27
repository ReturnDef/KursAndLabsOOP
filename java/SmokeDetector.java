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
            alert("дым обнаружен");
        } else {
            System.out.println(name + ": уровень дыма " + smokeLevel);
        }
    }

    public void perform(String command) {
        try {
            if (command.toLowerCase().contains("провер")) {
                setSmokeLevel(Math.random());
            } else {
                System.out.println(name + ": неизвестная команда");
            }
        } catch (Exception e) {
            System.out.println(name + ": ошибка команды датчика дыма: " + e.getMessage());
        }
    }

    @Override
    public String toString() {
        return super.toString() + " smoke=" + smokeLevel;
    }
}
