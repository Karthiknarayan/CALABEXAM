#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int target = 42;
#define arr_size 100

int binarySearch(int a[], int l, int r, int target) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target)
            return mid;
        if (a[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

int main() {
    int a[arr_size];
    int i, j;
    for (i = 0; i < arr_size; i++)
        a[i] = i;

    int res = -1;
    #pragma omp parallel shared(a, res)
    {
        int tid = omp_get_thread_num();
        int num = omp_get_num_threads();
        int chunk = arr_size / num;
        int l = tid * chunk;
        int r = (tid == num - 1) ? arr_size - 1 : (tid + 1) * chunk - 1;

        int loc = binarySearch(a, l, r, target);
        #pragma omp critical
        {
            if (loc != -1 && res == -1)
                res = loc;
        }
    }

    if (res == -1) {
        printf("target not found\n");
    } else {
        printf("element found at %d position\n", res);
    }
    return 0;
}
