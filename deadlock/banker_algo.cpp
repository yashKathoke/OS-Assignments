// bankers.cpp
#include <iostream>
#include <vector>
using namespace std;

void calculateNeedMatrix(const vector<vector<int>> &Max, const vector<vector<int>> &Allocation, vector<vector<int>> &Need, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

bool isSafeState(const vector<vector<int>> &Need, const vector<vector<int>> &Allocation, vector<int> &Available, int n, int m, vector<int> &safeSeq) {
    vector<int> Work = Available;
    vector<int> Finish(n, 0);
    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    safeSeq[count++] = i;
                    Finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    int n = 5, m = 3; // Hardcoded example: 5 processes, 3 resource types

    vector<vector<int>> Max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    vector<vector<int>> Allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<int> Available = {3, 3, 2};

    vector<vector<int>> Need(n, vector<int>(m));
    vector<int> safeSeq(n);

    calculateNeedMatrix(Max, Allocation, Need, n, m);

    if (isSafeState(Need, Allocation, Available, n, m, safeSeq)) {
        cout << "\nSystem is in SAFE state.\nSafe sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << " ";
        cout << "\n";
    } else {
        cout << "\nSystem is NOT in safe state.\n";
    }

    return 0;
}
