package smarthome;

import java.io.Serializable;
import java.util.*;

public class Scenario implements Serializable {

    private static final long serialVersionUID = 1L;

    private String id;
    private String name;
    private List<Action> actions = new ArrayList<>();
    private List<ConditionalAction> conditionalActions = new ArrayList<>();
    private boolean isActive = true;
    private int priority = 0;

    public Scenario(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() { return id; }

    public String getName() { return name; }

    public void addAction(Action a) {
        actions.add(a);
    }

    public void addConditionalAction(Action a, Condition cond) {
        conditionalActions.add(new ConditionalAction(a, cond));
    }

    public void execute(SmartHomeSystem system) {
        if (!isActive) {
            System.out.println("Сценарий отключен: " + name);
            return;
        }

        System.out.println("Выполнение сценария: " + name);

        for (Action a : actions) {
            try {
                a.execute(system);
            } catch (Exception e) {
                system.logError("Scenario action failed: " + e.toString());
            }
        }

        for (ConditionalAction ca : conditionalActions) {
            try {
                if (ca.cond == null || ca.cond.test(system)) {
                    ca.action.execute(system);
                }
            } catch (Exception e) {
                system.logError("ConditionalAction failed: " + e.toString());
            }
        }
    }

    @Override
    public String toString() {
        return id + ": " + name +
                " actions=" + actions.size() +
                " condActions=" + conditionalActions.size();
    }

    private static class ConditionalAction {
        Action action;
        Condition cond;

        ConditionalAction(Action a, Condition c) {
            this.action = a;
            this.cond = c;
        }
    }
}
