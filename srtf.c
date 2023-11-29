#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int ct;
};

void findWaitingTime(struct Process proc[], int n) {
    int tempBT[n];

    for (int i = 0; i < n; i++)
        tempBT[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].at <= t) && (tempBT[j] < minm) && tempBT[j] > 0) {
                minm = tempBT[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }
        t++;

        tempBT[shortest]--;

        minm = tempBT[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (tempBT[shortest] == 0) {
            complete++;
            check = 0;
            finish_time = t;

            proc[shortest].ct = finish_time;
            proc[shortest].tat = proc[shortest].ct - proc[shortest].at;
            proc[shortest].wt = proc[shortest].ct - (proc[shortest].at + proc[shortest].bt);
        }
    }
}

int main() {
    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    printf("Enter AT Sequentially:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i;
        scanf("%d", &proc[i].at);
    }

    printf("Enter BT Sequentially:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &proc[i].bt);
    }

    printf("\nPid  AT  BT  WT  TAT  CT\n");
    for (int i = 0; i < n; i++) {
        printf("%d    %d    %d    %d    %d    %d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].wt, proc[i].tat, proc[i].ct);
    }

    findWaitingTime(proc, n);

    printf("\nPid  AT  BT  WT  TAT  CT\n");
    float AWT = 0, ATAT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d    %d    %d    %d    %d    %d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].wt, proc[i].tat, proc[i].ct);
        AWT += proc[i].wt;
        ATAT += proc[i].tat;
    }

    printf("\nAverage WT = %.2f\n", AWT / n);
    printf("Average TAT = %.2f\n", ATAT / n);

    return 0;
}
