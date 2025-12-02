// optimal_page_replacement.cpp
#include <iostream>
#include <vector>
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

    vector<int> frames(frames_count, -1);  // -1 means empty frame
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = ref[i];

        // Check if page is already in frames (HIT?)
        bool hit = false;
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == page) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            // PAGE FAULT
            page_faults++;

            // Try to put in an empty frame first
            bool placed = false;
            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    placed = true;
                    break;
                }
            }

            // If no empty frame, apply OPTIMAL replacement
            if (!placed) {
                int replace_index = -1;
                int farthest_use = -1;

                // For each frame, see when its page will be used next
                for (int j = 0; j < frames_count; j++) {
                    int next_use = -1;

                    // Look ahead in the reference string
                    for (int k = i + 1; k < n; k++) {
                        if (ref[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }

                    // If page is never used again, replace it immediately
                    if (next_use == -1) {
                        replace_index = j;
                        break;
                    }

                    // Otherwise, track the page with farthest next use
                    if (next_use > farthest_use) {
                        farthest_use = next_use;
                        replace_index = j;
                    }
                }

                // Replace chosen frame with new page
                frames[replace_index] = page;
            }
        }
    }

    cout << "Total Page Faults (Optimal): " << page_faults << "\n";

    return 0;
}
