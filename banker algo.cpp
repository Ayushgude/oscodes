#include <iostream>
#include <vector>
using namespace std;

// Function to check if a process can be safely executed
bool canAllocate(const vector<int>& need, const vector<int>& available) {
    for (size_t i = 0; i < need.size(); i++) {
        if (need[i] > available[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int numProcesses, numResources;

    // Input number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> maximum(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<vector<int>> need(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);

    // Input Maximum matrix
    cout << "Enter the Maximum matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> maximum[i][j];
        }
    }

    // Input Allocation matrix
    cout << "Enter the Allocation matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Available resources
    cout << "Enter the Available resources:\n";
    for (int i = 0; i < numResources; i++) {
        cin >> available[i];
    }

    // Calculate the Need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    vector<bool> finished(numProcesses, false);
    vector<int> safeSequence;
    bool safeState = true;

    // Banker's Algorithm to find the safe sequence
    for (int count = 0; count < numProcesses; count++) {
        bool found = false;

        for (int i = 0; i < numProcesses; i++) {
            if (!finished[i] && canAllocate(need[i], available)) {
                // If the process can be safely executed
                for (int j = 0; j < numResources; j++) {
                    available[j] += allocation[i][j];
                }
                safeSequence.push_back(i);
                finished[i] = true;
                found = true;
                break;
            }
        }

        if (!found) {
            safeState = false;
            break;
        }
    }

    // Output the result
    if (safeState) {
        cout << "System is in a safe state.\nSafe sequence: ";
        for (int i : safeSequence) {
            cout << "P" << i << " ";
        }
        cout << endl;
    } else {
        cout << "System is not in a safe state.\n";
    }

    return 0;
}
//example
// maximum
// 4 2 1 2
// 5252
//2316
//1424
//3665
//allocation
//2001
//4221
//2103
//1312
//1432
//available
//2221
