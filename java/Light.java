package smarthome;

public class Light extends AbstractDevice {

    private int brightness;
    private String color;

    public Light(String id, String name, String location, int powerUsage, int brightness, String color) {
        super(id, name, location, powerUsage);
        this.brightness = brightness;
        this.color = color;
    }

    public void setBrightness(int b) {
        brightness = Math.max(0, Math.min(100, b));
        System.out.println(name + ": яркость " + brightness + "%");
    }

    public void setColor(String c) {
        color = c;
        System.out.println(name + ": цвет " + color);
    }

    public void dim() {
        setBrightness(Math.max(0, brightness - 10));
    }

    public void ecoMode() {
        setBrightness(20);
        System.out.println(name + ": режим экономии");
    }

    @Override
    public void perform(String command) {
        String c = command.toLowerCase();

        if (c.startsWith("вкл") || c.startsWith("turnon")) {
            turnOn();
        } else if (c.startsWith("выкл") || c.startsWith("turnoff")) {
            turnOff();
        } else if (c.startsWith("ярк") || c.startsWith("brightness")) {
            try {
                setBrightness(Integer.parseInt(command.replaceAll("[^0-9]", "")));
            } catch (Exception e) {
                System.out.println(name + ": неверная яркость");
            }
        } else if (c.startsWith("цвет") || c.startsWith("color")) {
            String[] parts = command.split(" ", 2);
            if (parts.length > 1) {
                setColor(parts[1]);
            } else {
                System.out.println(name + ": укажите цвет");
            }
        } else {
            System.out.println(name + ": неизвестная команда для лампы");
        }
    }

    @Override
    public String toString() {
        return super.toString() + " яркость=" + brightness + "%" + " цвет=" + color;
    }
}
