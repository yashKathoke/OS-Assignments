#include <iostream>
#include <vector>
#include <climits>

struct Process {
    int id;
    int arrival;
    int burst;
    int finish;
    int tat;
    int wt;
    bool done = false;
};

int main() {
    int n;
    std::cout << "Enter number of processes: ";
    std::cin >> n;

    std::vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        std::cout << "Enter arrival and burst time for P" << p[i].id << ": ";
        std::cin >> p[i].arrival >> p[i].burst;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = INT_MAX;

        // pick process with smallest burst among arrived & not done
        for (int i = 0; i < n; ++i) {
            if (!p[i].done && p[i].arrival <= time && p[i].burst < minBT) {
                minBT = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            // no process has arrived yet, CPU idle
            time++;
            continue;
        }

        // run selected process to completion
        time += p[idx].burst;
        p[idx].finish = time;
        p[idx].tat = p[idx].finish - p[idx].arrival;
        p[idx].wt = p[idx].tat - p[idx].burst;
        p[idx].done = true;
        completed++;
    }

    std::cout << "\nSJF (Non-preemptive):\n";
    std::cout << "P\tAT\tBT\tFT\tTAT\tWT\n";
    for (auto &pr : p) {
        std::cout << pr.id << "\t"
                  << pr.arrival << "\t"
                  << pr.burst << "\t"
                  << pr.finish << "\t"
                  << pr.tat << "\t"
                  << pr.wt << "\n";
    }

    return 0;
}
