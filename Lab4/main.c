#include "ex1.h"

int main(int argc , char **argv){
    printf("Chuong trinh test ex1:\n");

    displayBrkAddress();

    void *ptr0 = NULL;
    ptr0 = aligned_malloc(64,1024);
    displayBrkAddress();

    aligned_free(ptr0);
    displayBrkAddress();
    
    return 0;
}