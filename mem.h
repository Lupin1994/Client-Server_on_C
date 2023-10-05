#include <string.h>
#include <stdlib.h>

#define alloc_str(x) ((char *) alloc_mem(x + 1))

void *alloc_mem(size_t nbytes){ // обнуление выделенной памяти
    char *buf = (char*)malloc(nbytes);
    if (buf != NULL)
    {
        memset(buf, '\0', nbytes);
        return buf;
    }
    exit(-1);
}

void *calloc_mem(size_t n_elems, size_t elem_size){
    void *buf = calloc(n_elems, elem_size);
    if (buf != NULL)
    {
        return buf;
    }
    exit(-1);
}
