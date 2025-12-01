#include <iostream>
#include <vector>
#include <queue>

struct Process {
    int id;
    int arrival;
    int burst;
    int finish;
    int tat;
    int wt;
};

int main() {
    int n, quantum;
    std::cout << "Enter number of processes: ";
    std::cin >> n;

    std::vector<Process> p(n);
    std::vector<int> remBT(n);

    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        std::cout << "Enter arrival and burst time for P" << p[i].id << ": ";
        std::cin >> p[i].arrival >> p[i].burst;
        remBT[i] = p[i].burst;
    }

    std::cout << "Enter time quantum: ";
    std::cin >> quantum;

    std::queue<int> q;
    std::vector<bool> inQueue(n, false);

    int time = 0, completed = 0;

    // initially push all that arrive at time 0
    while (true) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!inQueue[i] && p[i].arrival <= time && remBT[i] > 0) {
                q.push(i);
                inQueue[i] = true;
                found = true;
            }
        }
        if (!q.empty() || found || completed == n)
            break;
        time++; // CPU idle initially if nothing has arrived
    }

    while (completed < n) {
        if (q.empty()) {
            // no ready process, jump time to next arrival
            int nextAT = 1e9;
            for (int i = 0; i < n; ++i) {
                if (remBT[i] > 0 && p[i].arrival < nextAT)
                    nextAT = p[i].arrival;
            }
            time = std::max(time, nextAT);
            // add newly arrived
            for (int i = 0; i < n; ++i) {
                if (!inQueue[i] && p[i].arrival <= time && remBT[i] > 0) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        int execTime = std::min(quantum, remBT[idx]);
        time += execTime;
        remBT[idx] -= execTime;

        // add any new arrivals during this time slice
        for (int i = 0; i < n; ++i) {
            if (!inQueue[i] && remBT[i] > 0 && p[i].arrival <= time) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (remBT[idx] == 0) {
            // finished
            p[idx].finish = time;
            p[idx].tat = p[idx].finish - p[idx].arrival;
            p[idx].wt = p[idx].tat - p[idx].burst;
            completed++;
        } else {
            // not finished, go back to queue
            q.push(idx);
        }
    }

    std::cout << "\nRound Robin:\n";
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
