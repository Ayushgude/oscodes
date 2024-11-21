#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> 
using namespace std;

// Structure to hold process information
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;    // Waiting time
};

// Function to calculate FCFS scheduling
void calculateFCFS(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Completion time
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }
        processes[i].completion = currentTime + processes[i].burst;
        currentTime = processes[i].completion;

        // Turnaround time: TAT = Completion time - Arrival time
        processes[i].turnaround = processes[i].completion - processes[i].arrival;

        // Waiting time: WT = TAT - Burst time
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
    }
}

void displayResults(const vector<Process>& processes) {
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& process : processes) {
        cout << "P" << process.pid << "\t"
             << process.arrival << "\t"
             << process.burst << "\t"
             << process.completion << "\t\t"
             << process.turnaround << "\t\t"
             << process.waiting << "\n";
    }
}

int main() {
    int n;

    // Input number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process P" << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process P" << i + 1 << ": ";
        cin >> processes[i].burst;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    // Calculate scheduling details
    calculateFCFS(processes);

    // Display results
    displayResults(processes);

    return 0;
}
