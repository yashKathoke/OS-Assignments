// lru_page_replacement.cpp
#include <iostream>
#include <vector>
#include <climits> // for INT_MAX
using namespace std;

int main() {
    int n, frames_count;

    cout << "Enter number of pages in reference string: ";
    cin >> n;

    vector<int> ref(n);
    cout << "Enter the reference string (page numbers): ";
    for (int i = 0; i < n; i++) {
        cin >> ref[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames_count;

    vector<int> frames(frames_count, -1);      // -1 means empty frame
    vector<int> last_used(frames_count, -1);   // when was this frame's page last used
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = ref[i];

        // Check if page is already in frames (HIT?)
        bool hit = false;
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == page) {
                hit = true;
                last_used[j] = i;  // update last used time
                break;
            }
        }

        if (!hit) {
            // PAGE FAULT
            page_faults++;

            // First, try to find an empty frame
            bool placed = false;
            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    last_used[j] = i;
                    placed = true;
                    break;
                }
            }

            // If no empty frame, apply LRU replacement
            if (!placed) {
                int lru_index = 0;
                int min_last_used = INT_MAX;

                // Find the frame whose last_used is smallest (least recently used)
                for (int j = 0; j < frames_count; j++) {
                    if (last_used[j] < min_last_used) {
                        min_last_used = last_used[j];
                        lru_index = j;
                    }
                }

                // Replace that frame with new page
                frames[lru_index] = page;
                last_used[lru_index] = i;
            }
        }
    }

    cout << "Total Page Faults (LRU): " << page_faults << "\n";

    return 0;
}
