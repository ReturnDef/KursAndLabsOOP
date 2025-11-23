package smarthome;

import java.time.*;

public class Notification {

    private String message;
    private LocalDateTime timestamp;
    private String imagePath;
    private boolean read;

    public Notification(String message) {
        this.message = message;
        this.timestamp = LocalDateTime.now();
    }

    public void send() {
        System.out.println("Уведомление: " + message);
    }

    public void show() {
        System.out.println(timestamp + ": " + message);
    }

    public void sendToDevice(Device d) {
        d.perform("notify " + message);
    }

    public void repeat() {
        System.out.println("Повтор уведомления: " + message);
    }

    public void attachImage(String p) {
        imagePath = p;
    }

    public void markAsRead() {
        read = true;
    }
}
