package smarthome;

import java.util.*;

public class EnergyManager {

    private double dailyConsumption;
    private List<String> optimizedDevices = new ArrayList<>();

    public void optimizeEnergy(SmartHomeSystem system) {
        System.out.println("Оптимизация энергопотребления...");
    }

    public void getEnergyReport(SmartHomeSystem system) {
        System.out.println("Отчет по энергии: устройства=" + system.getDevices().size());
    }

    public void predictUsage() {
        // тут будет что-то
    }

    public void collectData(SmartHomeSystem system) {
        System.out.println("Сбор данных с устройств...");
    }
}
