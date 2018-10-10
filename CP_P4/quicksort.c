#include <stdio.h>
#include <cilk/cilk.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>


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

static int partition (int * arr, int low, int  high)
{
    // pivot (Element to be placed at right position)
    int pivot = arr[high];  
 
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap (arr + i , arr + j);
        }
    }
    swap (arr + i + 1,  arr + high);
    return (i + 1);
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

// Quicksort recursion
static
void paralel_quicksort(int *L, int start, int end)
{
    if (start >= end)
        return;
  
    int splitPoint = partition(L, start, end);
    //printf("splitpoint: %d\n",splitPoint);

    cilk_spawn linear_quicksort(L, start, splitPoint - 1);
    cilk_spawn linear_quicksort(L, splitPoint + 1, end);

    cilk_sync;
}

void checkOrder(int *L, int size){

    //dump_list("SORTED LIST", L, 0,size);
    int* aux = L;

    for (int i = 0; i < size - 1; ++i, aux++){
        //printf("I:%d , I+1 : %d\n",*aux , *(aux + 1));
        assert(*aux <= *(aux + 1));

    }

    
}

int main(void)
{

    int times_to_repeat = 5;
    int size = 5000000;
    int *myList = malloc(sizeof(int) * size);
    int num;

    srand(time(NULL));
    float time_total = 0;
    

    for(int i = 0 ; i < times_to_repeat; i++){
        //dump_list("UNSORTED LIST", myList, 0,size);
        
        printf("generating list... \n");
        for (int j = 0; j < size; j++) {
            int num = rand() % 100;
            myList[j] = num;
        }
        printf("done generating list... \n");

        //dump_list("UNSORTED LIST", myList, 0,size);
        clock_t begin = clock();
    
        paralel_quicksort(myList, 0, size);

        clock_t end = clock();
        //dump_list("SORTED LIST", myList, 0,size);

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("time spent: %lf\n", time_spent);

        time_total+=time_spent;
        checkOrder(myList, size);

    }

    printf("average paralel: %lf\n\n" , time_total / times_to_repeat);


    time_total = 0;
    for(int i = 0 ; i < times_to_repeat; i++){
        
        
        printf("generating list... \n");
        for (int j = 0; j < size; j++) {
            int num = rand() % 100;
            myList[j] = num;
        }
        printf("done generating list... \n");

        // Save user and CPU start time
        //dump_list("UNSORTED LIST", myList, 0,size);

        clock_t begin = clock();
        linear_quicksort(myList, 0, size);
        clock_t end = clock();
        //dump_list("SORTED LIST", myList, 0,size);

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        time_total+=time_spent;
        checkOrder(myList, size);
    }
    printf("average linear: %f\n\n" , time_total / times_to_repeat);





  }