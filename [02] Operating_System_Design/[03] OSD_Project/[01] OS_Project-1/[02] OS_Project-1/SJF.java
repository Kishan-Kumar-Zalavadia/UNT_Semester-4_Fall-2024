import java.io.*;
import java.util.*;

public class SJF {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SJF <schedule_file>");
            return;
        }

        String filename = args[0];
        List<Task> tasks = readTasks(filename);
        System.out.println("Processes from file:");
        printTasks(tasks);
        scheduleSJF(tasks);
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

    private static void scheduleSJF(List<Task> tasks) {
        tasks.sort(Comparator.comparingInt(task -> task.burst)); // Sort by burst time
        FCFS.scheduleFCFS(tasks); // Use FCFS method to calculate metrics
    }
}
