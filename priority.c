#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct process {
    int priority;
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
};

struct process* calcWT(int n, struct process P[]) {
    struct process *res = malloc(n * sizeof(struct process));
    int burst[n];

    int curtime = 0;

    int completed = 0;
    int comp[n];
    for (int i = 0; i < n; i++) comp[i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (P[j].priority < P[i].priority) {
                struct process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        burst[i] = P[i].bt;
    }

    while (completed < n) {
        struct process current = P[0];
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

        curtime++;
        burst[k]--;

        if (burst[k] == 0) {
            completed++;
            comp[k] = 1;

            current.ct = curtime;
            current.tat = curtime - current.at;
            current.wt = current.ct - (current.at + current.bt);
            res[current.pid] = current;
        }
    }

    return res;
}

void printTableHeader() {
    printf("\n%4s  %4s  %4s  %4s  %4s  %4s  %4s\n", "Pid", "Pri", "AT", "BT", "WT", "TAT", "CT");
}

void printTableRow(struct process p) {
    printf("%4d  %4d  %4d  %4d  %4d  %4d  %4d\n", p.pid + 1, p.priority, p.at, p.bt, p.wt, p.tat, p.ct);
}

int main() {
    int n;

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    struct process *p = malloc(n * sizeof(struct process));

    printf("Enter AT Sequentially\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        scanf("%d", &p[i].at);
    }

    printf("Enter BT Sequentially\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
    }

    printf("Enter priority Sequentially\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].priority);
    }

    printTableHeader();
    for (int i = 0; i < n; i++) {
        printTableRow(p[i]);
    }

    struct process *res = calcWT(n, p);

    printf("*************************\n");

    printTableHeader();
    float AWT = 0;
    float ATAT = 0;
    for (int i = 0; i < n; i++) {
        printTableRow(res[i]);
        AWT += res[i].wt;
        ATAT += res[i].tat;
    }

    printf("\nAverage WT = %.2f\n", AWT / n);
    printf("Average TAT = %.2f\n", ATAT / n);

    free(p);
    free(res);

    return 0;
}
