#include <stdio.h>
#include <cilk/cilk.h>
#include <stdlib.h>
#include <sys/time.h>

// Swapping algorithm
static inline
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void dump_list(const char *tag, int *ptr, int left, int right)
{
    printf("%15s [%d..%d]: ", tag, left, right);
    for (int i = left; i <= right; i++)
        printf(" %3d", ptr[i]);
    putchar('\n');
}

// docker run -it -v /Users/nunomorais/Documents/Projects/CP_classes/CP_P4:/quick-sort aanciaes/cilkplus-pcre

// Partitioning algorithm
static
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 


// Quicksort recursion
static
void paralel_quicksort(int *L, int start, int end)
{
    if (start >= end)
        return;
    
    int splitPoint = partition(L, start, end);

    cilk_spawn paralel_quicksort(L, start, splitPoint - 1);
    cilk_spawn paralel_quicksort(L, splitPoint + 1, end);
    cilk_sync;
}

// Quicksort recursion
static
void linear_quicksort(int *L, int start, int end)
{
    if (start >= end)
        return;

    int splitPoint = partition(L, start, end);

    //dump_list("PRE-PARTITION", L, start, end);
    
    //dump_list("POST-PARTITION", L, start, end);
    //printf("Split point: %d\n", splitPoint);

    linear_quicksort(L, start, splitPoint - 1);
    linear_quicksort(L, splitPoint + 1, end);
  
    
}

int main(void)
{

    int times_to_repeat = 5;
    int size = 20000;
    int myList[size];
    int num;

    srand(time(NULL));

    struct timeval  tv1, tv2;
    

    for(int i = 0 ; i < times_to_repeat; i++){
        //dump_list("UNSORTED LIST", myList, 0,size);
        
        printf("generating list... \n");
        for (int i = 0; i < size; i++) {
            int num = rand();
            myList[i] = num;
        }
        printf("done generating list... \n");

        // Save user and CPU start time
        gettimeofday(&tv1, NULL);
        paralel_quicksort(myList, 0, size);
        /* stuff to do! */
        gettimeofday(&tv2, NULL);

        // Save user and CPU start time
        gettimeofday(&tv1, NULL);
        paralel_quicksort(myList, 0, size);
        /* stuff to do! */
        gettimeofday(&tv2, NULL);

        printf ("Total time = %f seconds\n\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

    }
    //printf("average paralel: %f\n\n" , time_total / times_to_repeat);


    //time_total = 0;
    for(int i = 0 ; i < times_to_repeat; i++){
        //dump_list("UNSORTED LIST", myList, 0,size);
        
        printf("generating list... \n");
        for (int i = 0; i < size; i++) {
            int num = rand();
            myList[i] = num;
        }
        printf("done generating list... \n");

        // Save user and CPU start time
        gettimeofday(&tv1, NULL);
        paralel_quicksort(myList, 0, size);
        /* stuff to do! */
        gettimeofday(&tv2, NULL);

        // Save user and CPU start time
        gettimeofday(&tv1, NULL);
        linear_quicksort(myList, 0, size);
        /* stuff to do! */
        gettimeofday(&tv2, NULL);

        printf ("Total time = %f seconds\n\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

    }
    //printf("average linear: %f\n\n" , time_total / times_to_repeat);





  }