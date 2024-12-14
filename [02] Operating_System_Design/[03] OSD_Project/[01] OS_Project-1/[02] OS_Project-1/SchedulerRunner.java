import java.io.*;
import java.util.*;

public class SchedulerRunner {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SchedulerRunner <schedule_file>");
            return;
        }

        String filename = args[0];

        String[] algorithms = {"FCFS", "SJF", "PriorityScheduling", "RR", "PriorityWithRR"};

        for (String algorithm : algorithms) {
            System.out.println("\n--- Running " + algorithm + " ---");
            runAlgorithm(algorithm, filename);
        }
    }

    private static void runAlgorithm(String algorithm, String filename) {
        try {
            ProcessBuilder pb = new ProcessBuilder("java", algorithm, filename);
            Process process = pb.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            process.waitFor();

        } catch (IOException | InterruptedException e) {
            System.err.println("Error running " + algorithm + ": " + e.getMessage());
        }
    }
}
