package smarthome;

public class LocationSensor {

    private String currentLocation = "unknown";

    public void updateLocation(String loc) {
        currentLocation = loc;
        System.out.println("Локация обновлена: " + loc);
    }

    public void triggerLocationBasedScenarios(SmartHomeSystem system) {
        for (Scenario s : system.getScenarios()) {
            s.execute(system);
        }
    }

    public String getCurrentLocation() {
        return currentLocation;
    }

    public boolean isAtHome() {
        return "home".equalsIgnoreCase(currentLocation);
    }
}
