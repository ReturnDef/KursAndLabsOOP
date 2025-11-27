package smarthome;

import java.io.Serializable;

public class Action implements Serializable {

    private static final long serialVersionUID = 1L;

    private String deviceId;
    private String command;
    private String argument;

    public Action(String deviceId, String command, String argument) {
        this.deviceId = deviceId;
        this.command = command;
        this.argument = argument;
    }

    public void execute(SmartHomeSystem system) {
        try {
            Device d = system.findDeviceById(deviceId);
            if (d == null) {
                String msg = "Устройство не найдено: " + deviceId;
                System.out.println(msg);
                system.logError(msg);
                return;
            }

            if (argument == null || argument.isEmpty()) {
                d.perform(command);
            } else {
                d.perform(command + " " + argument);
            }

        } catch (Exception e) {
            String msg = "Ошибка выполнения Action для device=" + deviceId + ": " + e.getMessage();
            System.out.println(msg);
            system.logError(msg);
        }
    }

    @Override
    public String toString() {
        return "Action{" +
                "deviceId='" + deviceId + '\'' +
                ", cmd='" + command + '\'' +
                ", arg='" + argument + '\'' +
                '}';
    }
}
