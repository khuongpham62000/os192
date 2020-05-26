#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PRNG_BUFSZ 32
#define NTHREADS 10000

/*Global Variable - Sum of inner point*/
int SOIP = 0;

/*Global Variable - Total point & Real point create*/
int totalPoint = 0;
int totalPointReal = 0;
#define PointPerThread totalPoint/NTHREADS

/* Function generate one point and return if it inside the circle */
void RandomPointRun(struct random_data* arg) {
    /* Random r1,r2 */
    int r1, r2;
    random_r(arg, &r1);
    random_r(arg, &r2);
    /* Calculate */
    r1 = r1 % 10000;
    r2 = r2 % 10000;
    int c = r1*r1 + r2*r2;
    
    totalPointReal++;
    if (c <= 100000000)
        ++SOIP;
}

/* Thread run here */
void* thread_run(void* arg) {
    for (int i = 0; i < PointPerThread; i++)
        RandomPointRun((struct random_data*) arg);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    /* Time start */
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* Check argv */
    if (argc != 2){
        printf("Please use: ./pi_multi-thread /*totalPoint*/\n");
        return -1;
    }
    totalPoint = atoi(argv[1]);
    if (totalPoint < 10000){
        printf("totalPoint >= 10000\n");
        return -1;
    }

    /* Set seed for random() */
    srandom(time(NULL));

    struct random_data* rand_states;
    char* rand_statebufs;
    pthread_t* thread_ids;
    int t = 0;
    /* Allocate memory */
    rand_states = (struct random_data*)calloc(NTHREADS, sizeof(struct random_data));
    rand_statebufs = (char*)calloc(NTHREADS, PRNG_BUFSZ);
    thread_ids = (pthread_t*)calloc(NTHREADS, sizeof(pthread_t));
    /* Create threads */
    for (t = 0; t < NTHREADS; t++) {
        /* for each thread, initialize a PRNG, seed is random() */
        initstate_r(random(), &rand_statebufs[t], PRNG_BUFSZ, &rand_states[t]);
        /* and create the thread to generate random point from that PRNG */
        pthread_create(&thread_ids[t], NULL, &thread_run, &rand_states[t]);
    }
    for (t = 0; t < NTHREADS; t++) {
        pthread_join(thread_ids[t], NULL);
    }
    /* Free memory */
    free(thread_ids);
    free(rand_states);
    free(rand_statebufs);

    printf("%i\n", SOIP);
    printf("%i\n", totalPointReal);
    printf("%i\n", totalPoint);

    /* Calculate pi */
    float pi = (float)4 * (float)SOIP / (float)totalPointReal;
    printf("Pi value  = %f\n", pi);
    
    /* Calculate time */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used = %f\n", cpu_time_used);
    pthread_exit (NULL);
}
