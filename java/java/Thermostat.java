package smarthome;

public class Thermostat extends AbstractDevice {

    private double targetTemp;
    private String mode;

    public Thermostat(String id, String name, String location, int powerUsage, double targetTemp) {
        super(id, name, location, powerUsage);
        this.targetTemp = targetTemp;
        this.mode = "auto";
    }

    public void setTargetTemp(double t) {
        targetTemp = t;
        System.out.println(name + ": цель " + targetTemp + "°C");
    }

    public void setMode(String m) {
        mode = m;
        System.out.println(name + ": режим " + mode);
    }

    public void perform(String command) {
        try {
            String c = command.toLowerCase();
            if (c.startsWith("вкл") || c.startsWith("turnon")) {
                turnOn();
            } else if (c.startsWith("выкл") || c.startsWith("turnoff")) {
                turnOff();
            } else if (c.startsWith("темп") || c.startsWith("temp")) {
                try {
                    String num = command.replaceAll("[^0-9.,-]", "").trim();
                    if (num.isEmpty()) throw new NumberFormatException("no number");
                    setTargetTemp(Double.parseDouble(num));
                } catch (NumberFormatException e) {
                    System.out.println(name + ": неверная температура");
                }
            } else {
                System.out.println(name + ": неизвестная команда для термостата");
            }
        } catch (Exception e) {
            System.out.println(name + ": ошибка выполнения команды термостата: " + e.getMessage());
        }
    }

    @Override
    public String toString() {
        return super.toString() + " цель=" + targetTemp + "C";
    }
}
