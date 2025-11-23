package smarthome;

public class DoorLock extends AbstractDevice {

    private boolean locked;

    public DoorLock(String id, String name, String location, int powerUsage) {
        super(id, name, location, powerUsage);
        locked = true;
    }

    public void lock() {
        locked = true;
        System.out.println(name + ": заблокирован");
    }

    public void unlock() {
        locked = false;
        System.out.println(name + ": разблокирован");
    }

    @Override
    public void perform(String command) {
        String c = command.toLowerCase();

        if (c.contains("lock") || c.contains("заблок")) {
            lock();
        } else if (c.contains("unlock") || c.contains("разблок")) {
            unlock();
        } else {
            System.out.println(name + ": неизвестная команда для замка");
        }
    }

    @Override
    public String toString() {
        return super.toString() + " locked=" + locked;
    }
}
