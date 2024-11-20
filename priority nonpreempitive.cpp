#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a process
struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int priority;       // Priority (lower value indicates higher priority)
    int completionTime; // Completion time
    int turnaroundTime; // Turnaround time
    int waitingTime;    // Waiting time
};

// Comparator for sorting by arrival time
bool compareByArrival(Process a, Process b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.priority < b.priority; // If arrival times are equal, sort by priority
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
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << processes[i].id << " (lower value = higher priority): ";
        cin >> processes[i].priority;
    }

    // Sort processes by arrival time and priority
    sort(processes.begin(), processes.end(), compareByArrival);

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Execute the selected process
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
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
