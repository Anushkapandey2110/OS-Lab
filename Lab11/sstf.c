#include <stdio.h>
#include <limits.h>

int SSTF(int queue[], int n, int header) {
    int visited[n];
    int i, j, min, pos, dist, sum;
    sum = 0;

    for(i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for(i = 0; i < n; i++) {
        min = INT_MAX;
        pos = -1;
        for(j = 0; j < n; j++) {
            dist = (header - queue[j]);
            if(dist < 0) {
                dist *= -1;
            }
            if(dist < min && !visited[j]) {
                min = dist;
                pos = j;
            }
        }
        visited[pos] = 1;
        header = queue[pos];
        sum += min;
    }
    return sum;
}

int main() {
    int n, header, val;
    printf("Enter number of tracks: ");
    scanf("%d", &n);
    int queue[n];
    printf("Enter tracks: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }
    printf("Enter header: ");
    scanf("%d", &header);
    val = SSTF(queue, n, header);
    printf("Overhead tracks: %d", val);
    return 0;
}
