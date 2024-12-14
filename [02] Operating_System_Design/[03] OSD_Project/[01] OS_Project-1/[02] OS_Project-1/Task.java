// Task.java
public class Task {
    String name;
    int priority;
    int burst;
    int remainingBurst;
    int waitingTime;
    int turnaroundTime;

    public Task(String name, int priority, int burst) {
        this.name = name;
        this.priority = priority;
        this.burst = burst;
        this.remainingBurst = burst;
        this.waitingTime = 0;
        this.turnaroundTime = 0;
    }
}
