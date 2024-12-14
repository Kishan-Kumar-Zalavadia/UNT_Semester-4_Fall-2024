import java.io.*;
import java.util.*;

public class FCFS {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FCFS <schedule_file>");
            return;
        }

        String filename = args[0];
        List<Task> tasks = readTasks(filename);
        System.out.println("Processes from file:");
        printTasks(tasks);
        scheduleFCFS(tasks);
    }

    private static List<Task> readTasks(String filename) {
        List<Task> tasks = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                String name = parts[0].trim();
                int priority = Integer.parseInt(parts[1].trim());
                int burst = Integer.parseInt(parts[2].trim());
                tasks.add(new Task(name, priority, burst));
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + filename);
            System.exit(1);
        }
        return tasks;
    }

    private static void printTasks(List<Task> tasks) {
        System.out.println("Task Name | Priority | CPU Burst");
        for (Task task : tasks) {
            System.out.printf("%-10s | %-8d | %-8d%n", task.name, task.priority, task.burst);
        }
    }

    public static void scheduleFCFS(List<Task> tasks) {
        int currentTime = 0;

        for (Task task : tasks) {
            task.waitingTime = currentTime;
            currentTime += task.burst;
            task.turnaroundTime = task.waitingTime + task.burst;

            System.out.println("Task " + task.name + ": Waiting Time = " + task.waitingTime + ", Turnaround Time = " + task.turnaroundTime);
        }

        calculateMetrics(tasks);
    }

    private static void calculateMetrics(List<Task> tasks) {
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;

        for (Task task : tasks) {
            totalWaitingTime += task.waitingTime;
            totalTurnaroundTime += task.turnaroundTime;
        }

        System.out.println("Average Waiting Time: " + (double) totalWaitingTime / tasks.size());
        System.out.println("Average Turnaround Time: " + (double) totalTurnaroundTime / tasks.size());
    }
}
