#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int needMatrix[100][100], allocated[100][100], Maximum[100][100], available[100];
bool isFinished[100];
int sequence[100];

void CalculateSafeSequence(int Pcount, int Rcount) {
    int i, j, work[100], count = 0;
    
    for (i = 0; i < Rcount; i++)
        work[i] = available[i];
    
    for (i = 0; i < 100; i++)
        isFinished[i] = false;

    while (count < Pcount) {
        bool canAllot = false;

        for (i = 0; i < Pcount; i++) {
            if (isFinished[i] == false) {
                for (j = 0; j < Rcount; j++) {
                    if (work[j] < needMatrix[i][j]) {
                        break;
                    }
                }

                if (j == Rcount) {
                    for (j = 0; j < Rcount; j++) {
                        work[j] += allocated[i][j];
                    }

                    sequence[count++] = i;
                    isFinished[i] = true;
                    canAllot = true;
                }
            }
        }

        if (canAllot == false) {
            printf("System is in NOT-SAFE state\n");
            return;
        }
    }

    printf("System is in SAFE state\n");
    printf("Safe sequence: ");
    
    for (i = 0; i < Pcount; i++)
        printf(" -> %d", sequence[i]);
    
    printf("\n");
}

int main() {
    int i, j, Pcount, Rcount;

    printf("Enter the number of Processes and Resources: ");
    scanf("%d %d", &Pcount, &Rcount);

    printf("Available Resource matrix:\n");
    for (i = 0; i < Rcount; i++)
        scanf("%d", &available[i]);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < Pcount; i++)
        for (j = 0; j < Rcount; j++)
            scanf("%d", &allocated[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < Pcount; i++)
        for (j = 0; j < Rcount; j++)
            scanf("%d", &Maximum[i][j]);

    for (i = 0; i < Pcount; i++)
        for (j = 0; j < Rcount; j++)
            needMatrix[i][j] = Maximum[i][j] - allocated[i][j];

    CalculateSafeSequence(Pcount, Rcount);

    return 0;
}
