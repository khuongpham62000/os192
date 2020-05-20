#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#define unitptr_t __UINTPTR_TYPE__

void* aligned_malloc(unsigned int size, unsigned int align);

void* aligned_free(void* ptr);

//Function Display Address of break
void  displayBrkAddress();