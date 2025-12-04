package smarthome;

import java.time.*;
import java.util.*;

public class Scheduler {

    private List<ScheduledItem> tasks = new ArrayList<>();

    public void add(String id, Scenario s, LocalDateTime when) {
        tasks.add(new ScheduledItem(id, s, when));
        System.out.println("Добавлено в расписание: " + id + " at " + when);
    }

    public void remove(String id) {
        tasks.removeIf(t -> t.id.equals(id));
    }

    public void runPendingActions(SmartHomeSystem system) {
        LocalDateTime now = LocalDateTime.now();
        Iterator<ScheduledItem> it = tasks.iterator();
        while (it.hasNext()) {
            ScheduledItem si = it.next();
            if (!si.when.isAfter(now)) {
                si.scenario.execute(system);
                it.remove();
            }
        }
    }

    public void runDailyRoutine(SmartHomeSystem system) {
        for (ScheduledItem si : tasks) {
            if (si.when.toLocalTime().equals(LocalTime.MIDNIGHT)) {
                si.scenario.execute(system);
            }
        }
    }

    public Optional<LocalDateTime> nextRunTime() {
        return tasks.stream().map(t -> t.when).min(LocalDateTime::compareTo);
    }

    public void clearSchedule() {
        tasks.clear();
    }

    private static class ScheduledItem {
        String id;
        Scenario scenario;
        LocalDateTime when;

        ScheduledItem(String id, Scenario s, LocalDateTime when) {
            this.id = id;
            this.scenario = s;
            this.when = when;
        }
    }
}
