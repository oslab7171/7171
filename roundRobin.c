#include <stdio.h>

#define MAX_PROCESS 100

int arr[MAX_PROCESS];
int f = -1, r = -1;

void enq(int p) {
    if (f == -1 && r == -1) {
        f = 0;
        r = 0;
        arr[r] = p;
    } else {
        arr[++r] = p;
    }
}

int deq() {
    if (f == r) {
        int temp = arr[f];
        f = -1;
        r = -1;
        return temp;
    } else {
        return arr[f++];
    }
}

int is_empty() {
    return (f == -1 && r == -1);
}

struct process {
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
    int arrived;
};

struct process* sort_with_at(struct process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    return p;
}

void calc(struct process p[], int n, int tq) {
    int comp[n];
    int tempbt[n];

    for (int i = 0; i < n; i++) {
        comp[i] = 0;
        tempbt[i] = p[i].bt;
    }

    sort_with_at(p, n);

    int time = 0;
    int count = 0;

    while (count < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && comp[i] == 0 && p[i].arrived == 0) {
                enq(p[i].pid);
                p[i].arrived = 1;
            }
        }

        if (is_empty()) {
            time++;
            continue;
        }

        int curpid = deq();

        if (tempbt[curpid] <= tq && tempbt[curpid] > 0) {
            count++;
            comp[curpid] = 1;
            time += tempbt[curpid];
            tempbt[curpid] = 0;
            p[curpid].ct = time;
            p[curpid].wt = p[curpid].ct - (p[curpid].at + p[curpid].bt);
            p[curpid].tat = time - p[curpid].at;
        } else {
            tempbt[curpid] -= tq;
            time += tq;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && comp[i] == 0 && p[i].arrived == 0) {
                    enq(p[i].pid);
                    p[i].arrived = 1;
                }
            }
            enq(curpid);
        }
    }
}

int main() {
    int tq;
    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("Enter AT Sequentially\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        p[i].arrived = 0;
        scanf("%d", &p[i].at);
    }

    printf("Enter BT Sequentially\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
    }

    printf("\nPid AT BT WT TAT CT\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", p[i].pid + 1, p[i].at, p[i].bt);
    }

    printf("Time Quantum = %d\n", tq);
    printf("*************************\n");

    calc(p, n, tq);

    printf("\nPid AT BT WT TAT CT\n");
    float AWT = 0;
    float ATAT = 0;

    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d %d %d\n", p[i].pid + 1, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
        AWT += p[i].wt;
        ATAT += p[i].tat;
    }

    printf("\nAverage WT = %.2f\n", AWT / n);
    printf("Average TAT = %.2f\n", ATAT / n);

    return 0;
}
