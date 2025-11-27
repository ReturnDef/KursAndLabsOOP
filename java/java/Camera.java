package smarthome;

public class Camera extends AbstractDevice {

    private boolean recording;
    private boolean motion;

    public Camera(String id, String name, String location, int powerUsage) {
        super(id, name, location, powerUsage);
        recording = false;
        motion = true;
    }

    public void startRecording() {
        recording = true;
        System.out.println(name + ": запись включена");
    }

    public void stopRecording() {
        recording = false;
        System.out.println(name + ": запись остановлена");
    }

    public void snapshot() {
        System.out.println(name + ": сделан снимок");
    }

    public void perform(String command) {
        try {
            String c = command.toLowerCase();
            if (c.startsWith("вкл") || c.startsWith("start")) {
                startRecording();
            } else if (c.startsWith("выкл") || c.startsWith("stop")) {
                stopRecording();
            } else if (c.startsWith("сним")) {
                snapshot();
            } else {
                System.out.println(name + ": неизвестная команда для камеры");
            }
        } catch (Exception e) {
            System.out.println(name + ": ошибка выполнения команды камеры: " + e.getMessage());
        }
    }

    public String toString() {
        return super.toString() + " recording=" + recording;
    }
}
