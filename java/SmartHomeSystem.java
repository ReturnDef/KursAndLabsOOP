package smarthome;

import java.util.*;

public class SmartHomeSystem {

    private Map<String, Device> devices = new LinkedHashMap<>();
    private Map<String, Scenario> scenarios = new LinkedHashMap<>();
    private List<Event> events = new ArrayList<>();
    private List<Notification> notifications = new ArrayList<>();
    private Scheduler scheduler = new Scheduler();
    private EnergyManager energyManager = new EnergyManager();

    public void addDevice(Device d) {
        devices.put(d.getId(), d);
        System.out.println("Добавлено устройство: " + d.getName());
    }

    public void removeDevice(String id) {
        devices.remove(id);
        System.out.println("Удалено: " + id);
    }

    public Collection<Device> getDevices() {
        return devices.values();
    }

    public Device findDeviceById(String id) {
        return devices.get(id);
    }

    public Device findDeviceByName(String name) {
        return devices.values().stream()
                .filter(d -> d.getName().equals(name))
                .findFirst()
                .orElse(null);
    }

    public void addScenario(Scenario s) {
        scenarios.put(s.getId(), s);
        System.out.println("Сценарий добавлен: " + s.getName());
    }

    public Collection<Scenario> getScenarios() {
        return scenarios.values();
    }

    public Scenario getScenarioById(String id) {
        return scenarios.get(id);
    }

    public void triggerEvent(Event e) {
        events.add(e);
        e.trigger(this);
    }

    public void sendNotification(Notification n) {
        notifications.add(n);
        n.send();
    }

    public Scheduler getScheduler() {
        return scheduler;
    }

    public EnergyManager getEnergyManager() {
        return energyManager;
    }

    public void showDevices() {
        if (devices.isEmpty()) {
            System.out.println("Устройств нет");
            return;
        }
        for (Device d : devices.values()) {
            System.out.println(d.toString());
        }
    }

    public void showScenarios() {
        if (scenarios.isEmpty()) {
            System.out.println("Сценариев нет");
            return;
        }
        for (Scenario s : scenarios.values()) {
            System.out.println(s.toString());
        }
    }

    public void showEventLog() {
        if (events.isEmpty()) {
            System.out.println("Событий нет");
        } else {
            for (Event e : events) {
                System.out.println(e.getInfo());
            }
        }
    }
}
