#ifndef H_L
#define H_L

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct List List;
    struct List
    {
        void* data;
        List* next;
    };

    void insertion_list(List **list, void* new_data, size_t data_size);
    void printList(List* list);



#endif
