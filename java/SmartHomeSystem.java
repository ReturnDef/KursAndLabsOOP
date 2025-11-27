package smarthome;

import java.util.*;
import java.time.*;

public class SmartHomeSystem {

    public enum Role { ADMIN, USER, GUEST }

    private Map<String, Device> devices = new LinkedHashMap<>();
    private Map<String, Scenario> scenarios = new LinkedHashMap<>();
    private List<Event> events = new ArrayList<>();
    private List<Notification> notifications = new ArrayList<>();

    private Scheduler scheduler = new Scheduler();
    private EnergyManager energyManager = new EnergyManager();

    private List<String> eventLog = new ArrayList<>();
    private List<String> errorLog = new ArrayList<>();

    private double totalEnergyUsage = 0.0;

    public void addDevice(Device d) {
        if (d == null) return;

        if (devices.containsKey(d.getId())) {
            String msg = "Device ID already exists: " + d.getId();
            System.out.println(msg);
            logError(msg);
            return;
        }

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

    public List<Device> getDevicesList() {
        return new ArrayList<>(devices.values());
    }

    public Device findDeviceById(String id) {
        return devices.get(id);
    }

    public Device findDeviceByName(String name) {
        return devices.values()
                .stream()
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
        String info = LocalDateTime.now() + " " + e.getInfo();
        eventLog.add(info);
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
        if (eventLog.isEmpty()) {
            System.out.println("Событий нет");
        } else {
            for (String e : eventLog) System.out.println(e);
        }
    }

    public void logError(String msg) {
        String rec = LocalDateTime.now() + " ERROR: " + msg;
        errorLog.add(rec);
    }

    public void showErrorLog() {
        if (errorLog.isEmpty()) System.out.println("Ошибок нет");
        else errorLog.forEach(System.out::println);
    }

    public void safeTurnOnDevice(String id) {
        Device d = findDeviceById(id);

        if (d == null) {
            String msg = "Не найдено устройство " + id;
            System.out.println(msg);
            logError(msg);
            return;
        }

        try {
            d.turnOn();
            totalEnergyUsage += d.getPowerUsage();
        } catch (Exception e) {
            logError("safeTurnOnDevice: " + e.toString());
        }
    }

    public void safeTurnOffDevice(String id) {
        Device d = findDeviceById(id);

        if (d == null) {
            String msg = "Не найдено устройство " + id;
            System.out.println(msg);
            logError(msg);
            return;
        }

        try {
            d.turnOff();
        } catch (Exception e) {
            logError("safeTurnOffDevice: " + e.toString());
        }
    }

    public double getTotalEnergyUsage() {
        return totalEnergyUsage;
    }

    public void sendNotificationToDeviceId(String deviceId, String msg) {
        try {
            Device d = findDeviceById(deviceId);

            if (d == null)
                throw new IllegalArgumentException("Device not found: " + deviceId);

            Notification n = new Notification(msg);
            n.sendToDevice(d);

            notifications.add(n);

        } catch (Exception e) {
            logError("sendNotificationToDeviceId: " + e.toString());
            System.out.println("Ошибка уведомления: " + e.getMessage());
        }
    }

    public void showNotifications() {
        if (notifications.isEmpty())
            System.out.println("Уведомлений нет");
        else
            notifications.forEach(Notification::show);
    }

    public Optional<Scenario> safeFindScenario(String id) {
        return Optional.ofNullable(scenarios.get(id));
    }

    public void registerTrigger(String deviceId, java.util.function.Consumer<AbstractDevice> cb) {
        Device d = findDeviceById(deviceId);

        if (d == null) {
            logError("registerTrigger: device not found " + deviceId);
            return;
        }

        if (d instanceof AbstractDevice)
            ((AbstractDevice) d).addListener(cb);
    }
}
