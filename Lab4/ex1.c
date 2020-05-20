#include "ex1.h"

void* aligned_malloc(unsigned int size, unsigned int align){
    // Initialize
    void* ptr;
    ptr = sbrk(0);
    unitptr_t ptrAddress = (unitptr_t) ptr;
    //Check out of mem or size == 0
    if (sbrk(size) == (void*)-1||size == 0) return NULL;
    else {
        if ((ptrAddress%(unitptr_t)align) == 0) return ptr;
        else
        {
            // Scale brkAddress
            brk(ptr);
            ptr = sbrk(align - ptrAddress%align);
            return aligned_malloc(size,align);
        }
    }
}

void* aligned_free(void* ptr){
    if (ptr == NULL)
        return NULL;
    else
    {
        brk(ptr);
        return sbrk(0);
    }
}

void displayBrkAddress(){
    void *brkaddress = NULL;
    brkaddress = sbrk(0);
    printf("%p\n",brkaddress);
}
