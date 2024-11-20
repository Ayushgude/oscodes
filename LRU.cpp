#include <iostream>
#include <vector>
#include <unordered_map>
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

    // LRU Page Replacement Logic
    unordered_map<int, int> pagesInMemory; // Tracks pages and their last used time
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        int page = referenceString[i];

        // Check if the page is not in memory
        if (pagesInMemory.find(page) == pagesInMemory.end()) {
            // Page fault occurred
            pageFaults++;

            // If memory is full, remove the least recently used page
            if (pagesInMemory.size() == numFrames) {
                int lruPage = -1, oldestTime = i;
                for (auto& p : pagesInMemory) {
                    if (p.second < oldestTime) {
                        oldestTime = p.second;
                        lruPage = p.first;
                    }
                }
                pagesInMemory.erase(lruPage);
            }
        }

        // Update the last used time of the page
        pagesInMemory[page] = i;
    }

    // Output the number of page faults
    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}
// example- 3213416343421452134
//frame size -3