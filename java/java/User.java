package smarthome;

import java.util.*;

public class User {

    private String userID;
    private String name;
    private SmartHomeSystem.Role role;
    private Map<String, String> preferences = new HashMap<>();

    public User(String id, String name) {
        this.userID = id;
        this.name = name;
        this.role = SmartHomeSystem.Role.USER;
    }

    public void executeScenario(SmartHomeSystem system, Scenario s) {
        if (role == SmartHomeSystem.Role.GUEST) {
            System.out.println("Недостаточно прав");
            return;
        }
        s.execute(system);
    }

    public void setPreference(String k, String v) {
        preferences.put(k, v);
    }

    public Map<String, String> getPreferences() {
        return preferences;
    }

    public void login(String u, String p) {
        System.out.println(name + " вошел в систему");
    }

    public void logout() {
        System.out.println(name + " вышел");
    }

    public void setRole(SmartHomeSystem.Role r) {
        this.role = r;
    }

    public SmartHomeSystem.Role getRole() {
        return role;
    }

    public String getUserID() {
        return userID;
    }
}
