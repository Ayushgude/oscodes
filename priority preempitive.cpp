#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

// Structure to represent a process
struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int remainingTime;  // Remaining burst time
    int priority;       // Priority (lower value indicates higher priority)
    int completionTime; // Completion time
    int turnaroundTime; // Turnaround time
    int waitingTime;    // Waiting time
};

int main() {
    int n;

    // Input number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << processes[i].id << " (lower value = higher priority): ";
        cin >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Execute the selected process for 1 unit of time
            processes[idx].remainingTime--;
            currentTime++;

            // If the process is completed
            if (processes[idx].remainingTime == 0) {
                completed++;
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            }
        } else {
            // If no process is ready, increment time
            currentTime++;
        }
    }

    // Display the results
    cout << "\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << "P" << p.id << "\t" 
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.priority << "\t\t"
             << p.completionTime << "\t\t"
             << p.turnaroundTime << "\t\t"
             << p.waitingTime << "\n";
    }

    // Calculate and display average TAT and WT
    float avgTAT = 0, avgWT = 0;
    for (const auto& p : processes) {
        avgTAT += p.turnaroundTime;
        avgWT += p.waitingTime;
    }
    avgTAT /= n;
    avgWT /= n;

    cout << "\nAverage Turnaround Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
