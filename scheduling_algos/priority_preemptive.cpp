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
};

int main() {
    int n;
    std::cout << "Enter number of processes: ";
    std::cin >> n;

    std::vector<Process> p(n);
    std::vector<int> remBT(n);

    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        std::cout << "Enter AT, BT and Priority for P" << p[i].id << ": ";
        std::cin >> p[i].arrival >> p[i].burst >> p[i].priority;
        remBT[i] = p[i].burst;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int bestPrio = INT_MAX;

        // at this time, pick highest priority among arrived & remaining
        for (int i = 0; i < n; ++i) {
            if (remBT[i] > 0 && p[i].arrival <= time) {
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

        // run this process for 1 unit of time
        remBT[idx]--;
        time++;

        if (remBT[idx] == 0) {
            completed++;
            p[idx].finish = time;
            p[idx].tat = p[idx].finish - p[idx].arrival;
            p[idx].wt = p[idx].tat - p[idx].burst;
        }
    }

    std::cout << "\nPreemptive Priority:\n";
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
