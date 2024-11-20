#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Structure to represent a process
struct Process {
    int id;          // Process ID
    int arrivalTime; // Arrival time
    int burstTime;   // CPU burst time
    int completionTime; // Completion time
    int turnaroundTime; // Turnaround time
    int waitingTime;    // Waiting time
};

// Comparator function for sorting by arrival time and then by burst time
bool compareByArrivalAndBurst(Process a, Process b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.burstTime < b.burstTime;
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
    }

    // Sort processes by arrival time and then by burst time
    sort(processes.begin(), processes.end(), compareByArrivalAndBurst);

    int currentTime = 0; // Tracks current time
    for (int i = 0; i < n; i++) {
        // Find the next process to execute
        int idx = -1;
        int minBurst = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].completionTime == 0) {
                if (processes[j].burstTime < minBurst) {
                    minBurst = processes[j].burstTime;
                    idx = j;
                }
            }
        }

        // If no process is available, move time forward
        if (idx == -1) {
            currentTime++;
            i--;
            continue;
        }

        // Execute the process
        currentTime += processes[idx].burstTime;
        processes[idx].completionTime = currentTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
    }

    // Display the result
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
