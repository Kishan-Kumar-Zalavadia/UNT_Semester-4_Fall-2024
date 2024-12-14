import java.io.*;
import java.util.*;

public class AnalyzeScheduler {

    public static void main(String[] args) {
        String directoryPath = "data/";
        String[] algorithms = {"FCFS", "SJF", "PriorityScheduling", "RR", "PriorityWithRR"};
        File folder = new File(directoryPath);
        File[] listOfFiles = folder.listFiles((dir, name) -> name.endsWith(".txt"));

        if (listOfFiles == null || listOfFiles.length == 0) {
            System.out.println("No schedule files found in the directory: " + directoryPath);
            return;
        }

        Map<String, List<ResultMetrics>> algorithmResults = new HashMap<>();
        Map<String, Map<String, ResultMetrics>> allResults = new HashMap<>();

        for (File scheduleFile : listOfFiles) {
            System.out.println("-------------------------------------------------------------");
            System.out.println("\nRunning algorithms for file: " + scheduleFile.getName());

            Map<String, ResultMetrics> fileResults = new HashMap<>();

            for (String algorithm : algorithms) {
                System.out.println("\n--- Running " + algorithm + " on " + scheduleFile.getName() + " ---");
                ResultMetrics metrics = runAlgorithm(algorithm, scheduleFile.getPath());
                fileResults.put(algorithm, metrics);
                algorithmResults.computeIfAbsent(algorithm, k -> new ArrayList<>()).add(metrics);
            }

            allResults.put(scheduleFile.getName(), fileResults);
        }

        System.out.println("-------------------------------------------------------------");
        saveResultsToTxt(allResults, "all_results.txt");

        analyzeResults(algorithmResults);
    }

    private static ResultMetrics runAlgorithm(String algorithm, String filename) {
        try {
            ProcessBuilder pb = new ProcessBuilder("java", algorithm, filename);
            Process process = pb.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            ResultMetrics metrics = new ResultMetrics();
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
                if (line.contains("Average Waiting Time")) {
                    metrics.waitingTime = Double.parseDouble(line.split(":")[1].trim());
                } else if (line.contains("Average Turnaround Time")) {
                    metrics.turnaroundTime = Double.parseDouble(line.split(":")[1].trim());
                }
            }

            process.waitFor();
            return metrics;

        } catch (IOException | InterruptedException e) {
            System.err.println("Error running " + algorithm + ": " + e.getMessage());
            return null;
        }
    }

    private static void saveResultsToTxt(Map<String, Map<String, ResultMetrics>> allResults, String filePath) {
        try (FileWriter writer = new FileWriter(filePath)) {
            for (Map.Entry<String, Map<String, ResultMetrics>> fileEntry : allResults.entrySet()) {
                writer.write("Results for: " + fileEntry.getKey() + "\n");
                for (Map.Entry<String, ResultMetrics> algorithmEntry : fileEntry.getValue().entrySet()) {
                    ResultMetrics metrics = algorithmEntry.getValue();
                    writer.write("Algorithm: " + algorithmEntry.getKey() + "\n");
                    writer.write("  Average Waiting Time: " + metrics.waitingTime + "\n");
                    writer.write("  Average Turnaround Time: " + metrics.turnaroundTime + "\n");
                    writer.write("\n");
                }
                writer.write("---------------------------------------------------\n");
            }
            System.out.println("All results saved to " + filePath);
        } catch (IOException e) {
            System.err.println("Error writing to text file: " + e.getMessage());
        }
    }

    private static void analyzeResults(Map<String, List<ResultMetrics>> algorithmResults) {
        for (String algorithm : algorithmResults.keySet()) {
            List<ResultMetrics> metricsList = algorithmResults.get(algorithm);
            double totalWaitingTime = 0, totalTurnaroundTime = 0;
            int count = metricsList.size();

            for (ResultMetrics metrics : metricsList) {
                totalWaitingTime += metrics.waitingTime;
                totalTurnaroundTime += metrics.turnaroundTime;
            }

            System.out.println("\nAlgorithm: " + algorithm);
            System.out.printf("Average Waiting Time: %.2f\n", totalWaitingTime / count);
            System.out.printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / count);
        }
    }
}

class ResultMetrics {
    double waitingTime;
    double turnaroundTime;
}
