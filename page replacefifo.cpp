#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int main() {
    int numFrames, numPages;

    // Input number of frames
    cout << "Enter the number of page frames: ";
    cin >> numFrames;

    // Input the number of pages in the reference string
    cout << "Enter the number of pages in the reference string: ";
    cin >> numPages;

    vector<int> referenceString(numPages);

    // Input the reference string
    cout << "Enter the reference string (space-separated): ";
    for (int i = 0; i < numPages; i++) {
        cin >> referenceString[i];
    }

    // FIFO Page Replacement Logic
    unordered_set<int> pagesInMemory; // Tracks pages currently in memory
    queue<int> fifoQueue;             // FIFO queue to track order of pages
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        int page = referenceString[i];

        // Check if the page is not in memory
        if (pagesInMemory.find(page) == pagesInMemory.end()) {
            // Page fault occurred
            pageFaults++;

            // If memory is full, remove the oldest page
            if (fifoQueue.size() == numFrames) {
                int pageToRemove = fifoQueue.front();
                fifoQueue.pop();
                pagesInMemory.erase(pageToRemove);
            }

            // Add the new page to memory and queue
            fifoQueue.push(page);
            pagesInMemory.insert(page);
        }
    }

    // Output the number of page faults
    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}
// example- 3213416343421452134
//frame size -3

