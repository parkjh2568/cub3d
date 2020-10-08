#include <stdio.h>
#define MAX 100000

typedef struct twodimen
{
    int x;
    int y;
}twod;

void swap(twod arr[], int a, int b);
int partition(twod arr[], int left, int right);
void quicksort(twod arr[], int left, int right);

int main(void)
{
    int n;
    twod dot[MAX];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
    scanf("%d %d", &dot[i].x, &dot[i].y);
    }
    quicksort(dot, 0, n - 1);
    for (int i = 0; i < n; i++) {
    printf("%d %d\n", dot[i].x, dot[i].y);
    }
}

void swap(twod arr[], int a, int b)
{
    twod temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int partition(twod arr[], int left, int right)
{
    int pivot = left;
    int low = left + 1;
    int high = right;
    while (low <= high) {
        while (arr[pivot].y >= arr[low].y) {
            if (arr[pivot].y == arr[low].y) {
                if (arr[pivot].x > arr[low].x)
                    low++;
                else
                    break; 
            }
            else
                low++;
        }
        while (arr[pivot].y <= arr[high].y) {
            if (arr[pivot].y == arr[high].y) {
                if (arr[pivot].x < arr[high].x)
                    high--;
                else
                    break;
            }
            else
                high--;
        }
        if (low <= high)
            swap(arr, low, high); 
    }
    swap(arr, left, high);
    return high;
}

void quicksort(twod arr[], int left, int right)
{
    if (left <= right) {
        int pivot = partition(arr, left, right); 
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}
