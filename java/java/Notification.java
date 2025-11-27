package smarthome;
import java.time.*;
public class Notification {
    private String message;
    private LocalDateTime timestamp;
    private String imagePath;
    private boolean read;
    public Notification(String message) { this.message = message; this.timestamp = LocalDateTime.now(); }
    public void send() {
        try {
            if (message == null || message.trim().isEmpty()) throw new IllegalArgumentException("Пустое сообщение");
            System.out.println("Уведомление: " + message);
        } catch (Exception e) {
            System.out.println("Ошибка при отправке уведомления: " + e.getMessage());
        }
    }
    public void show() { System.out.println(timestamp + ": " + message); }
    public void sendToDevice(Device d) {
        try {
            if (d == null) throw new IllegalArgumentException("Устройство null");
            d.perform("notify " + message);
        } catch (Exception e) { System.out.println("Ошибка при отправке уведомления устройству: " + e.getMessage()); }
    }
    public void repeat() { System.out.println("Повтор уведомления: " + message); }
    public void attachImage(String p) { imagePath = p; }
    public void markAsRead() { read = true; }
}
