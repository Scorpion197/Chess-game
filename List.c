#include "List.h"


void insertion_list(List **plist, void* new_data, size_t data_size)
{
    /* Creation of a new list element */
    List *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new_node->data = malloc(data_size);
    new_node->next = (*plist);

    // Copy contents of new_data to newly allocated memory.
    // Assumption: char takes 1 byte.
    int i;
    for (i=0; i<data_size; i++)
        *(char *)(new_node->data + i) = *(char *)(new_data + i);


    (*plist) = new_node;

}

void printList(List* list) {

    List* node = list;

    while (node != NULL)
      {
          printf("%d |", *(int*)(node->data) );
          node = node->next;
      }


}
