import java.io.*;
import java.util.*;

public class PriorityWithRR {
    private static final int TIME_QUANTUM = 10;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PriorityWithRR <schedule_file>");
            return;
        }

        String filename = args[0];
        List<Task> tasks = readTasks(filename);
        System.out.println("Processes from file:");
        printTasks(tasks);
        schedulePriorityRR(tasks);
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

    private static void schedulePriorityRR(List<Task> tasks) {
        PriorityQueue<Task> readyQueue = new PriorityQueue<>((a, b) -> Integer.compare(b.priority, a.priority)); // Max-heap for priority
        int currentTime = 0;
        int index = 0;

        while (index < tasks.size() || !readyQueue.isEmpty()) {
            while (index < tasks.size()) {
                readyQueue.offer(tasks.get(index++));
            }

            if (!readyQueue.isEmpty()) {
                Task task = readyQueue.poll();
                if (task.remainingBurst <= TIME_QUANTUM) {
                    currentTime += task.remainingBurst;
                    task.turnaroundTime = currentTime;
                    task.waitingTime = task.turnaroundTime - task.burst;
                    task.remainingBurst = 0;
                } else {
                    currentTime += TIME_QUANTUM;
                    task.remainingBurst -= TIME_QUANTUM;
                    readyQueue.offer(task);
                }
            }
        }

        calculateMetrics(tasks);
    }

    private static void calculateMetrics(List<Task> tasks) {
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;

        for (Task task : tasks) {
            totalWaitingTime += task.waitingTime;
            totalTurnaroundTime += task.turnaroundTime;

            System.out.println("Task " + task.name + ": Waiting Time = " + task.waitingTime + ", Turnaround Time = " + task.turnaroundTime);
        }

        System.out.println("Average Waiting Time: " + (double) totalWaitingTime / tasks.size());
        System.out.println("Average Turnaround Time: " + (double) totalTurnaroundTime / tasks.size());
    }
}
