package smarthome;

public class EnergyMeter extends AbstractDevice {

    private double total;

    public EnergyMeter(String id, String name, String location, int powerUsage) {
        super(id, name, location, powerUsage);
        total = 0.0;
    }

    public void addUsage(double a) {
        total += a;
        System.out.println(name + ": добавлено " + a);
    }

    public double getTotal() {
        return total;
    }

    @Override
    public void perform(String command) {
        System.out.println(name + ": команда -> " + command);
    }

    @Override
    public String toString() {
        return super.toString() + " total=" + total;
    }
}
