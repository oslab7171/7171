#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Process {
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
};

typedef struct Process Process;

Process *calcWT(int n, Process *P) {
    Process *res = (Process *)malloc(n * sizeof(Process));
    int curtime = 0;
    int comp[n];
    for (int i = 0; i < n; i++)
        comp[i] = 0;
    int noofexecuted = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (P[j].bt < P[i].bt) {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }

    while (noofexecuted < n) {
        Process current = P[0];
        int k = -1;
        for (int i = 0; i < n; i++) {
            if (P[i].at <= curtime && comp[i] == 0) {
                current = P[i];
                k = i;
                break;
            }
        }

        if (k == -1) {
            curtime++;
            continue;
        }

        comp[k] = 1;
        noofexecuted++;

        current.wt = curtime - current.at;
        curtime += current.bt;
        current.ct = curtime;
        current.tat = curtime - current.at;
        res[current.pid] = current;
    }

    return res;
}

int main() {
    int n;

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));

    printf("Enter AT Sequentially:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        scanf("%d", &p[i].at);
    }

    printf("Enter BT Sequentially:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
    }

    printf("\nPid  at  BT  WT  TAT  CT\n");
    Process *res = calcWT(n, p);

    float AWT = 0, ATAT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d    %d    %d    %d    %d    %d\n", res[i].pid + 1, res[i].at, res[i].bt, res[i].wt, res[i].tat, res[i].ct);
        AWT += res[i].wt;
        ATAT += res[i].tat;
    }

    printf("\nAverage WT = %.2f\n", AWT / n);
    printf("Average TAT = %.2f\n", ATAT / n);

    free(p);
    free(res);

    return 0;
}
