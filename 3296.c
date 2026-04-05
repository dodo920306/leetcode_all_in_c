#include <stdio.h>
#include <math.h>
#include <stdbool.h>

long long minNumberOfSeconds(int mountainHeight, int* workerTimes, int workerTimesSize);
bool isAbleToMakeMountainHeight0(long long time, int mountainHeight, int* workerTimes, int workerTimesSize);

int main() {
    printf("%lld\n", minNumberOfSeconds(4, (int[]){2, 1, 1}, 3));
    printf("%lld\n", minNumberOfSeconds(10, (int[]){3, 2, 2, 4}, 4));
    printf("%lld\n", minNumberOfSeconds(5, (int[]){1}, 1));
    return 0;
}

long long minNumberOfSeconds(int mountainHeight, int* workerTimes, int workerTimesSize) {
    /* get the average work time */
    long long averageWorkerTime = workerTimes[0];
    for (int i = 1; i < workerTimesSize; i++) {
        averageWorkerTime += workerTimes[i];
    }
    averageWorkerTime /= workerTimesSize;

    /**
     * Make the upper bound of time as the time spent by the worker 
     * with average workerTime reducing the whole mountain alone:
     * avg(workerTimes) * ((h * (h + 1)) / 2).
     */
    long long averageWorkerTimeForMountainHeight = averageWorkerTime * mountainHeight * (mountainHeight + 1) / 2;
    /* start Binary seach (with the lower bound as 0) */
    for (long long i = 0; averageWorkerTimeForMountainHeight - i > 1;) {
        long long time = (i + averageWorkerTimeForMountainHeight) / 2;
        if (isAbleToMakeMountainHeight0(time, mountainHeight, workerTimes, workerTimesSize)) {
            averageWorkerTimeForMountainHeight = time;
        } else {
            i = time;
        }
    }
    return averageWorkerTimeForMountainHeight;
}

bool isAbleToMakeMountainHeight0(long long time, int mountainHeight, int* workerTimes, int workerTimesSize) {
    long long totalHeightReducedByWorkersInTime = 0;
    for (int i = 0; i < workerTimesSize; i++) {
        /**
         * The height h of mountain a worker can reduct in time T satisfy:
         * t * ((h * (h + 1)) / 2) <= T
         * => ((h * (h + 1)) / 2) <= T / t
         * => h^2 + h <= 2T / t
         * => h^2 + h - (2T / t) <= 0
         * => h <= (-1 + sqrt(1 + 8T / t)) / 2
         * Since C helps us to round down the result by converting it to an integer,
         * we can simply say
         * h = (-1 + sqrt(1 + 8T / t)) / 2.
         */
        totalHeightReducedByWorkersInTime += (-1 + sqrt(1 + 8 * time / workerTimes[i])) / 2;
        /**
         * return if workers can possibly reduce the whole mountain in time.
         */
        if (totalHeightReducedByWorkersInTime >= mountainHeight) {
            return true;
        }
    }
    return false;
}
