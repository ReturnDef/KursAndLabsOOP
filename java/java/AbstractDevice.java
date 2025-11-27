package smarthome;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public abstract class AbstractDevice implements Device {

    public enum State { ON, OFF, ERROR, SLEEP, ALARM }

    protected String id;
    protected String name;
    protected String location;
    protected boolean isOn;
    protected int powerUsage;
    protected State state = State.OFF;
    protected List<Consumer<AbstractDevice>> listeners = new ArrayList<>();

    public AbstractDevice(String id, String name, String location, int powerUsage) {
        this.id = id;
        this.name = name;
        this.location = location;
        this.powerUsage = powerUsage;
        this.isOn = false;
        this.state = State.OFF;
    }

    public String getId() { return id; }

    public String getName() { return name; }

    public String getLocation() { return location; }

    public void setName(String name) { this.name = name; }

    public void setLocation(String location) { this.location = location; }

    public void turnOn() {
        try {
            isOn = true;
            state = State.ON;
            System.out.println(name + " включено");
            notifyListeners();
        } catch (Exception e) {
            state = State.ERROR;
            System.out.println(name + ": ошибка при включении: " + e.getMessage());
        }
    }

    public void turnOff() {
        try {
            isOn = false;
            state = State.OFF;
            System.out.println(name + " выключено");
            notifyListeners();
        } catch (Exception e) {
            state = State.ERROR;
            System.out.println(name + ": ошибка при выключении: " + e.getMessage());
        }
    }

    public boolean isOn() { return isOn; }

    public int getPowerUsage() { return powerUsage; }

    public State getState() { return state; }

    public void setState(State s) { this.state = s; }

    @Override
    public String toString() {
        return id + ": " + name + " (" + location + ") "
                + (isOn ? "[вкл]" : "[выкл]") + " state=" + state;
    }

    public void perform(String command) {
        System.out.println(name + ": команда '" + command + "' не распознана");
    }

    public void addListener(Consumer<AbstractDevice> cb) {
        if (cb != null) listeners.add(cb);
    }

    public void removeListener(Consumer<AbstractDevice> cb) {
        listeners.remove(cb);
    }

    protected void notifyListeners() {
        for (Consumer<AbstractDevice> cb : listeners) {
            try {
                cb.accept(this);
            } catch (Exception e) {
                System.out.println(name + ": ошибка при уведомлении слушателя: " + e.getMessage());
            }
        }
    }

    public boolean selfTest() {
        try {
            System.out.println(name + ": выполняется self-test");
            if (id == null || id.isEmpty())
                throw new RuntimeException("Invalid id");
            return true;
        } catch (Exception e) {
            state = State.ERROR;
            System.out.println(name + ": self-test провален: " + e.getMessage());
            return false;
        }
    }

    public void alert(String reason) {
        System.out.println("ALERT from " + name + ": " + reason);
        state = State.ALARM;
        notifyListeners();
    }
}
