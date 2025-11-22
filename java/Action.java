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
        Device d = system.findDeviceById(deviceId);

        if (d == null) {
            System.out.println("Устройство не найдено: " + deviceId);
            return;
        }

        if (argument == null || argument.isEmpty()) {
            d.perform(command);
        } else {
            d.perform(command + " " + argument);
        }
    }

    @Override
    public String toString() {
        return "Action{" + "deviceId='" + deviceId + '\'' + ", cmd='" + command + '\'' + ", arg='" + argument + '\'' + '}';
    }
}
