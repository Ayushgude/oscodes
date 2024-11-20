#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm> // Include this for std::find

using namespace std;

int findFarthestFutureIndex(const vector<int>& referenceString, const vector<int>& frames, int currentIndex) {
    int farthestIndex = -1, farthestDistance = -1;

    for (int i = 0; i < frames.size(); i++) {
        int nextUse = -1;
        for (int j = currentIndex + 1; j < referenceString.size(); j++) {
            if (referenceString[j] == frames[i]) {
                nextUse = j;
                break;
            }
        }
        if (nextUse == -1) {
            return i; // This page is never used again, so we replace it
        }
        if (nextUse > farthestDistance) {
            farthestDistance = nextUse;
            farthestIndex = i;
        }
    }

    return farthestIndex;
}

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

    vector<int> frames; // Stores pages in memory
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        int page = referenceString[i];

        // Check if the page is already in memory
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            // Page fault occurred
            pageFaults++;

            // If memory is full, replace a page
            if (frames.size() == numFrames) {
                int indexToReplace = findFarthestFutureIndex(referenceString, frames, i);
                frames[indexToReplace] = page;
            } else {
                frames.push_back(page);
            }
        }
    }

    // Output the number of page faults
    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}

// example- 3213416343421452134
//frame size -3