#include <iostream>
#include <vector>
#include <climits>

struct Process {
    int id;
    int arrival;
    int burst;
    int priority;
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
        std::cout << "Enter AT, BT and Priority for P" << p[i].id << ": ";
        std::cin >> p[i].arrival >> p[i].burst >> p[i].priority;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int bestPrio = INT_MAX;

        // pick highest priority (lowest number) among arrived & not done
        for (int i = 0; i < n; ++i) {
            if (!p[i].done && p[i].arrival <= time) {
                if (p[i].priority < bestPrio) {
                    bestPrio = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].burst;
        p[idx].finish = time;
        p[idx].tat = p[idx].finish - p[idx].arrival;
        p[idx].wt = p[idx].tat - p[idx].burst;
        p[idx].done = true;
        completed++;
    }

    std::cout << "\nNon-preemptive Priority:\n";
    std::cout << "P\tAT\tBT\tPr\tFT\tTAT\tWT\n";
    for (auto &pr : p) {
        std::cout << pr.id << "\t"
                  << pr.arrival << "\t"
                  << pr.burst << "\t"
                  << pr.priority << "\t"
                  << pr.finish << "\t"
                  << pr.tat << "\t"
                  << pr.wt << "\n";
    }

    return 0;
}
