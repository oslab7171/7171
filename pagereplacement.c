#include <stdio.h>
#include <stdlib.h>

void fifo(int ref[], int size, int n) {
    int frames[n];
    for (int i = 0; i < n; i++) {
        frames[i] = -1;
    }
    int pageMiss = 0;
    int pageHits = 0;
    int currentIndex = 0;
    for (int i = 0; i < size; i++) {
        int flag = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            pageHits++;
        } else {
            frames[currentIndex] = ref[i];
            currentIndex = (currentIndex + 1) % n;
            pageMiss++;
        }
    }
    printf("FIFO Page Faults: %d, Page Hits: %d\n", pageMiss, pageHits);
}

void optimal(int ref[], int size, int n) {
    int frames[n];
    for (int i = 0; i < n; i++) {
        frames[i] = -1;
    }
    int pageMiss = 0;
    int pageHits = 0;
    for (int i = 0; i < size; i++) {
        int flag = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            pageHits++;
        } else {
            int farthest = -1;
            int replaceIndex = -1;
            for (int j = 0; j < n; j++) {
                int foundNext = 0;
                for (int k = i + 1; k < size; k++) {
                    if (frames[j] == ref[k]) {
                        foundNext = 1;
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (foundNext == 0) {
                    replaceIndex = j;
                    break;
                }
            }
            frames[replaceIndex] = ref[i];
            pageMiss++;
        }
    }
    printf("Optimal Page Faults: %d, Page Hits: %d\n", pageMiss, pageHits);
}

void lru(int ref[], int size, int n) {
    int frames[n];
    int time[n];
    for (int i = 0; i < n; i++) {
        frames[i] = -1;
        time[i] = 0;
    }
    int pageMiss = 0;
    int pageHits = 0;
    for (int i = 0; i < size; i++) {
        int flag = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                time[j] = i;
                break;
            }
        }
        if (flag == 1) {
            pageHits++;
        } else {
            int oldest = 0;
            for (int j = 0; j < n; j++) {
                if (time[j] < time[oldest]) {
                    oldest = j;
                }
            }
            frames[oldest] = ref[i];
            time[oldest] = i;
            pageMiss++;
        }
    }
    printf("LRU Page Faults: %d, Page Hits: %d\n", pageMiss, pageHits);
}

int main(void) {
    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    int size;
    printf("Enter the size of the reference string: ");
    scanf("%d", &size);
    int ref[size];
    printf("Enter the reference string: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &ref[i]);
    }
    printf("\nResults for all page replacement algorithms:\n");
    fifo(ref, size, frames);
    optimal(ref, size, frames);
    lru(ref, size, frames);
    return 0;
}
