// fcfs.cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;
    int arrival;
    int burst;
    int finish;
    int tat;
    int wt;
};

int main() {
    int n;
    std::cout << "Enter number of processes: ";
    std::cin >> n;

    std::vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        std::cout << "Enter arrival and burst time for P" << i + 1 << ": ";
        std::cin >> p[i].arrival >> p[i].burst;
    }

    // Sort by arrival time (FCFS order)
    std::sort(p.begin(), p.end(), 
        [](const Process& a, const Process& b) {
            return a.arrival < b.arrival;
        }
    );

    int time = 0;

    for (auto &pr : p) {
        if (time < pr.arrival)
            time = pr.arrival;     // CPU idle
        
        time += pr.burst;
        pr.finish = time;
        pr.tat = pr.finish - pr.arrival;
        pr.wt = pr.tat - pr.burst;
    }

    std::cout << "\nP\tAT\tBT\tFT\tTAT\tWT\n";
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
