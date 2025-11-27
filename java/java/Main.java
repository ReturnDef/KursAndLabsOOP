package smarthome;
import java.util.*;
import java.time.*;
public class Main {
    private static Scanner sc = new Scanner(System.in);
    private static SmartHomeSystem system = new SmartHomeSystem();
    public static void main(String[] args) {
        seedDemo();
        boolean run = true;
        while (run) {
            System.out.println("\n=== УМНЫЙ ДОМ ===");
            System.out.println("1) Управление устройствами");
            System.out.println("2) Управление сценариями");
            System.out.println("3) Планировщик");
            System.out.println("4) События и уведомления");
            System.out.println("5) Триггеры и self-test");
            System.out.println("0) Выход");
            System.out.print("Выберите: ");
            String cmd = sc.nextLine().trim();
            try {
                switch (cmd) {
                    case "1": devicesMenu(); break;
                    case "2": scenariosMenu(); break;
                    case "3": schedulerMenu(); break;
                    case "4": eventsMenu(); break;
                    case "5": triggersMenu(); break;
                    case "0": run = false; break;
                    default: System.out.println("Неверная команда"); break;
                }
            } catch (Exception e) {
                System.out.println("Ошибка: " + e.getMessage());
                system.logError("Unhandled exception in main loop: " + e.toString());
            }
        }
        System.out.println("Завершение работы");
    }
    private static void seedDemo() {
        system.addDevice(new Light("L1", "Люстра", "Гостиная", 10, 75, "белый"));
        system.addDevice(new Thermostat("T1", "Термостат", "Прихожая", 5, 21.0));
        system.addDevice(new DoorLock("D1", "Входной замок", "Дверь", 1));
        system.addDevice(new Camera("C1", "Камера", "Коридор", 3));
    }
    private static void devicesMenu() {
        while (true) {
            System.out.println("\n-- Устройства --");
            System.out.println("1) Добавить устройство");
            System.out.println("2) Показать устройства");
            System.out.println("3) Настроить устройство");
            System.out.println("4) Удалить устройство");
            System.out.println("0) Назад");
            String c = sc.nextLine().trim();
            if (c.equals("0")) return;
            if (c.equals("1")) addDeviceInteractive();
            else if (c.equals("2")) system.showDevices();
            else if (c.equals("3")) configureDeviceInteractive();
            else if (c.equals("4")) {
                System.out.print("ID: ");
                String id = sc.nextLine().trim();
                try { system.removeDevice(id); } catch (Exception e) { System.out.println("Ошибка при удалении: " + e.getMessage()); }
            } else { System.out.println("Неверная команда"); }
        }
    }
    private static void addDeviceInteractive() {
        System.out.println("Типы: 1) Лампа 2) Термостат 3) Замок 4) Камера 5) Ороситель 6) Жалюзи 7) Датчик дыма 8) Счетчик энергии");
        System.out.print("Выберите тип: ");
        String t = sc.nextLine().trim();
        System.out.print("ID: ");
        String id = sc.nextLine().trim();
        System.out.print("Имя: ");
        String name = sc.nextLine().trim();
        System.out.print("Локация: ");
        String loc = sc.nextLine().trim();
        System.out.print("Потребление W: ");
        int pw = 0;
        try { pw = Integer.parseInt(sc.nextLine().trim()); } catch (Exception e) { System.out.println("Неверный ввод числа, установлено 0"); }
        try {
            switch (t) {
                case "1": System.out.print("Яркость: "); int b = Integer.parseInt(sc.nextLine().trim()); System.out.print("Цвет: "); String col = sc.nextLine().trim(); system.addDevice(new Light(id, name, loc, pw, b, col)); break;
                case "2": System.out.print("Температура: "); double temp = Double.parseDouble(sc.nextLine().trim()); system.addDevice(new Thermostat(id, name, loc, pw, temp)); break;
                case "3": system.addDevice(new DoorLock(id, name, loc, pw)); break;
                case "4": system.addDevice(new Camera(id, name, loc, pw)); break;
                case "5": system.addDevice(new Sprinkler(id, name, loc, pw)); break;
                case "6": System.out.print("Позиция: "); int pos = Integer.parseInt(sc.nextLine().trim()); system.addDevice(new Blinds(id, name, loc, pw, pos)); break;
                case "7": system.addDevice(new SmokeDetector(id, name, loc, pw)); break;
                case "8": system.addDevice(new EnergyMeter(id, name, loc, pw)); break;
                default: System.out.println("Неизвестный тип"); break;
            }
        } catch (Exception e) {
            System.out.println("Ошибка при создании устройства: " + e.getMessage());
            system.logError("addDeviceInteractive: " + e.toString());
        }
    }
    private static void configureDeviceInteractive() {
        System.out.print("ID устройства: ");
        String id = sc.nextLine().trim();
        Device d = system.findDeviceById(id);
        if (d == null) { System.out.println("Не найдено"); return; }
        System.out.println("Устройство: " + d.getName());
        System.out.println("1) Включить 2) Выключить 3) Выполнить команду 0) Назад");
        String cmd = sc.nextLine().trim();
        try {
            if (cmd.equals("1")) system.safeTurnOnDevice(id);
            else if (cmd.equals("2")) system.safeTurnOffDevice(id);
            else if (cmd.equals("3")) { System.out.print("Команда: "); String c = sc.nextLine(); d.perform(c); }
        } catch (Exception e) { System.out.println("Ошибка при управлении устройством: " + e.getMessage()); system.logError("configureDeviceInteractive: " + e.toString()); }
    }
    private static void scenariosMenu() {
        while (true) {
            System.out.println("\n-- Сценарии --");
            System.out.println("1) Добавить сценарий");
            System.out.println("2) Показать сценарии");
            System.out.println("3) Добавить действие в сценарий");
            System.out.println("4) Выполнить сценарий");
            System.out.println("0) Назад");
            String c = sc.nextLine().trim();
            if (c.equals("0")) return;
            if (c.equals("1")) { System.out.print("ID сценария: "); String id = sc.nextLine().trim(); System.out.print("Название: "); String name = sc.nextLine().trim(); system.addScenario(new Scenario(id, name)); }
            else if (c.equals("2")) system.showScenarios();
            else if (c.equals("3")) addActionToScenarioInteractive();
            else if (c.equals("4")) executeScenarioInteractive();
            else System.out.println("Неверная команда");
        }
    }
    private static void addActionToScenarioInteractive() {
        System.out.print("ID сценария: ");
        String sid = sc.nextLine().trim();
        Scenario s = system.getScenarioById(sid);
        if (s == null) { System.out.println("Сценарий не найден"); return; }
        System.out.print("ID устройства: ");
        String did = sc.nextLine().trim();
        System.out.print("Команда (например: turnOn, turnOff, brightness 50): ");
        String cmd = sc.nextLine().trim();
        String[] parts = cmd.split(" ", 2);
        String command = parts[0];
        String arg = parts.length > 1 ? parts[1] : "";
        s.addAction(new Action(did, command, arg));
        System.out.println("Действие добавлено");
    }
    private static void executeScenarioInteractive() {
        System.out.print("ID сценария: ");
        String sid = sc.nextLine().trim();
        Scenario s = system.getScenarioById(sid);
        if (s == null) { System.out.println("Сценарий не найден"); return; }
        s.execute(system);
    }
    private static void schedulerMenu() {
        while (true) {
            System.out.println("\n-- Планировщик --");
            System.out.println("1) Добавить задачу");
            System.out.println("2) Выполнить ожидаемые задачи");
            System.out.println("3) Очистить расписание");
            System.out.println("0) Назад");
            String c = sc.nextLine().trim();
            if (c.equals("0")) return;
            if (c.equals("1")) {
                System.out.print("ID задачи: ");
                String id = sc.nextLine().trim();
                System.out.print("ID сценария: ");
                String sid = sc.nextLine().trim();
                Scenario s = system.getScenarioById(sid);
                if (s == null) { System.out.println("Сценарий не найден"); continue; }
                System.out.print("Дата и время (YYYY-MM-DDTHH:MM): ");
                String when = sc.nextLine().trim();
                try { system.getScheduler().add(id, s, LocalDateTime.parse(when)); } catch (Exception e) { System.out.println("Неверный формат"); }
            } else if (c.equals("2")) system.getScheduler().runPendingActions(system);
            else if (c.equals("3")) system.getScheduler().clearSchedule();
            else System.out.println("Неверная команда");
        }
    }
    private static void eventsMenu() {
        while (true) {
            System.out.println("\n-- События и уведомления --");
            System.out.println("1) Триггер события");
            System.out.println("2) Показать лог событий");
            System.out.println("3) Отправить уведомление");
            System.out.println("0) Назад");
            String c = sc.nextLine().trim();
            if (c.equals("0")) return;
            if (c.equals("1")) {
                System.out.print("Описание: ");
                String d = sc.nextLine().trim();
                system.triggerEvent(new Event(d));
            } else if (c.equals("2")) system.showEventLog();
            else if (c.equals("3")) {
                System.out.print("Сообщение: ");
                String m = sc.nextLine().trim();
                system.sendNotification(new Notification(m));
            } else { System.out.println("Неверная команда"); }
        }
    }
    private static void triggersMenu() {
        while (true) {
            System.out.println("\n-- Триггеры и self-test --");
            System.out.println("1) Зарегистрировать триггер для устройства (при изменении состояния)"); 
            System.out.println("2) Вызвать self-test для всех устройств");
            System.out.println("3) Показать журнал ошибок");
            System.out.println("0) Назад");
            String c = sc.nextLine().trim();
            if (c.equals("0")) return;
            if (c.equals("1")) {
                System.out.print("ID устройства: "); String id = sc.nextLine().trim();
                Device d = system.findDeviceById(id);
                if (d == null) { System.out.println("Не найдено"); continue; }
                if (d instanceof AbstractDevice) {
                    ((AbstractDevice)d).addListener(dev -> {
                        String msg = "Событие устройства: " + dev.getName() + " state=" + dev.getState();
                        system.triggerEvent(new Event(msg));
                        system.sendNotification(new Notification(msg));
                    });
                }
                System.out.println("Триггер зарегистрирован для " + d.getName());
            } else if (c.equals("2")) {
                System.out.println("Запуск self-test для всех устройств..."); 
                for (Device d : system.getDevices()) {
                    try { if (d instanceof AbstractDevice) ((AbstractDevice)d).selfTest(); } catch (Exception e) { system.logError("selfTest: " + e.toString()); }
                }
            } else if (c.equals("3")) { system.showErrorLog(); }
            else System.out.println("Неверная команда");
        }
    }
}
