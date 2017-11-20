#include <stdio.h>
#include <stdlib.h>

typedef struct el {
    int val;
    struct el* next;
} El;

typedef struct list {
    El* first;
} LinkedList;

int main()
{

    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));

    for (El* tmp = l->first; tmp != NULL; tmp = tmp->next)
        printf("%d ", tmp->val);

    return 0;
}
