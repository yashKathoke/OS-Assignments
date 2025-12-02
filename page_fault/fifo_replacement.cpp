// fifo_page_replacement.cpp
#include <iostream>
#include <vector>

int main() {
    int n, frames_count;
    
    std::cout << "Enter number of pages in reference string: ";
    std::cin >> n;

    std::vector<int> ref(n);
    std::cout << "Enter the reference string (page numbers): ";
    for (int i = 0; i < n; i++) {
        std::cin >> ref[i];
    }

    std::cout << "Enter number of frames: ";
    std::cin >> frames_count;

    std::vector<int> frames(frames_count, -1); // -1 means empty frame
    int page_faults = 0;
    int victim = 0; // index of frame to be replaced (FIFO pointer)

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

            // If there is an empty frame, use it
            bool placed = false;
            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    placed = true;
                    break;
                }
            }

            // If no empty frame, replace using FIFO
            if (!placed) {
                frames[victim] = page;
                victim = (victim + 1) % frames_count;
            }
        }
    }

    std::cout << "Total Page Faults (FIFO): " << page_faults << "\n";

    return 0;
}
