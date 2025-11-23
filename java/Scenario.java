package smarthome;

import java.io.Serializable;
import java.util.*;

public class Scenario implements Serializable {

    private static final long serialVersionUID = 1L;

    private String id;
    private String name;
    private List<Action> actions = new ArrayList<>();
    private boolean isActive = true;
    private int priority = 0;

    public Scenario(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void addAction(Action a) {
        actions.add(a);
    }

    public void execute(SmartHomeSystem system) {
        if (!isActive) {
            System.out.println("Сценарий отключен: " + name);
            return;
        }
        System.out.println("Выполнение сценария: " + name);
        for (Action a : actions) {
            a.execute(system);
        }
    }

    @Override
    public String toString() {
        return id + ": " + name + " actions=" + actions.size();
    }
}
