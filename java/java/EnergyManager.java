package smarthome;

import java.util.*;

public class EnergyManager {

    private double dailyConsumption;
    private List<String> optimizedDevices = new ArrayList<>();

    public void optimizeEnergy(SmartHomeSystem system) {
        System.out.println("Оптимизация энергопотребления...");
        double total = system.getTotalEnergyUsage();

        if (total > 1000) {
            System.out.println("Высокое потребление: " + total + ", включаем ECO режим для ламп.");
            system.getDevices()
                    .stream()
                    .filter(d -> d instanceof Light)
                    .forEach(d -> ((Light) d).ecoMode());
        }
    }

    public void getEnergyReport(SmartHomeSystem system) {
        System.out.println(
                "Отчет по энергии: устройства=" + system.getDevices().size() +
                        " total=" + system.getTotalEnergyUsage()
        );
    }

    public void predictUsage() {}

    public void collectData(SmartHomeSystem system) {
        System.out.println("Сбор данных с устройств...");
    }
}
