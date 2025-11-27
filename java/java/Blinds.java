package smarthome;

public class Blinds extends AbstractDevice {

    private int position;

    public Blinds(String id, String name, String location, int powerUsage, int position) {
        super(id, name, location, powerUsage);
        this.position = position;
    }

    public void setPosition(int p) {
        position = Math.max(0, Math.min(100, p));
        System.out.println(name + ": положение " + position + "%");
    }

    public void open() {
        setPosition(100);
    }

    public void close() {
        setPosition(0);
    }

    public void perform(String command) {
        try {
            String c = command.toLowerCase();

            if (c.contains("open") || c.contains("откр")) {
                open();
            } else if (c.contains("close") || c.contains("закр")) {
                close();
            } else {
                String num = command.replaceAll("[^0-9]", "").trim();
                if (num.isEmpty()) throw new NumberFormatException("no number");
                setPosition(Integer.parseInt(num));
            }

        } catch (NumberFormatException e) {
            System.out.println(name + ": неверная команда (ожидается число)");
        } catch (Exception e) {
            System.out.println(name + ": ошибка команды: " + e.getMessage());
        }
    }

    public String toString() {
        return super.toString() + " position=" + position;
    }
}
