#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct sthread_args {
    int sim_nr;
    int *res;
};


void simulate(struct sthread_args args) {

    srand((unsigned int) (time(NULL) + 1));

    double curr_x, curr_y;
    for (int i = 0; i < args.sim_nr; i++) {

        curr_x = drand48() / RAND_MAX;
        curr_y = drand48() / RAND_MAX;

        if (curr_x * curr_x + curr_y * curr_y <= 1)
            args.res++;
    }
}


int main(int argc, char const *argv[]) {


    int thread_nr = atoi(argv[1]);
    int sim_nr = atoi(argv[2]);

    pthread_t threads[thread_nr];
    int res[thread_nr];
    int remainder = sim_nr % thread_nr;
    int sim_per_thread = sim_nr / thread_nr;


    for (int i = 0; i < thread_nr; i++, remainder--) {

        struct sthread_args *args = args;
        args->res = &res[i];

        if (remainder > 0) args->sim_nr = sim_per_thread++;
        else args->sim_nr = sim_per_thread;


        pthread_t id = malloc(sizeof(pthread_t));
        pthread_create(&id, NULL, (void *(*)(void *)) simulate, (void *) args);
        threads[i] = id;

    }

    void *lol;
    for (int i = 0; i < thread_nr; i++) {
        pthread_join(threads[i], lol);
    }


    int total_hits = 0;
    for (int i = 0; i < thread_nr; i++) {
        total_hits += res[i];

    }

    float p = (float) total_hits / sim_nr;
    float pi = p * 4;

    printf("%f", pi);

}
