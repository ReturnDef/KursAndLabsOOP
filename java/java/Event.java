package smarthome;

public class Event {

    private String description;

    public Event(String description) {
        this.description = description;
    }

    public void trigger(SmartHomeSystem system) {
        System.out.println("Событие: " + description);
    }

    public String getInfo() {
        return description;
    }
}
