#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MAX
using namespace std;

// Structure to represent a process
struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int remainingTime;  // Remaining time (for preemptive scheduling)
    int completionTime; // Completion time
    int turnaroundTime; // Turnaround time
    int waitingTime;    // Waiting time
};

// Comparator function for sorting by arrival time
bool compareByArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;

    // Input number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Process IDs
        cout << "Enter arrival time for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareByArrival);

    int currentTime = 0;
    int completed = 0;
    int totalProcesses = n;

    while (completed != totalProcesses) {
        int idx = -1;
        int minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemainingTime) {
                    minRemainingTime = processes[i].remainingTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Execute the process for 1 unit of time
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
            // No process is available, increment time
            currentTime++;
        }
    }

    // Display the results
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << "P" << p.id << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t\t"
             << p.turnaroundTime << "\t\t"
             << p.waitingTime << "\n";
    }

    // Average Turnaround Time and Waiting Time
    float avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (const auto& p : processes) {
        avgTurnaroundTime += p.turnaroundTime;
        avgWaitingTime += p.waitingTime;
    }
    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;

    return 0;
}
