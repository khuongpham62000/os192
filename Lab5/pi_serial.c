#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Global Variable - Sum of inner point*/
int SOIP = 0;

/*Global Variable - Total point & Real point create*/
int totalPoint = 0;
int totalPointReal = 0;

/* Function generate points and check if they're inside the circle */
void PointGenerator() {
    while (totalPointReal < totalPoint){
        ++totalPointReal;
        /* Random r1,r2 */
        int r1, r2;
        r1 = random();
        r2 = random();
        /* Calculate */
        r1 = r1 % 10000;
        r2 = r2 % 10000;
        int c = r1*r1 + r2*r2;
        if (c <= 100000000)
            ++SOIP;
    }
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

    PointGenerator();

    /* Calculate pi */
    float pi = (float)4 * (float)SOIP / (float)totalPointReal;
    printf("Pi value  = %f\n", pi);
    /* Calculate time */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used = %f\n", cpu_time_used);
    return 0;
}
