#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

typedef struct element
{
    int val;
    struct element *next;
}element;

typedef struct delement
{
    struct delement *prev;
    int val;
    struct delement *next;
}delement;

void initialize_list(element **);
element * sortedInsertion(element *, int);
element * createNode(int);
void printList(element *);
element * headInsertion(element *, int);
element * bottomInsertion(element *, int);
void * doublesOdd(element *);
element * deleteTen(element *);
void handleList(element **);
element * insertEven(element *);
int searchElement(element *, int);
element * deleteElement(element *, int);
element * searchMax(element *);
element * searchMin(element *);
void initialize_Dlist(delement **);
delement * dSortedInsertion(delement *, int);
delement * dHeadInsertion(delement *, int);
delement * dBottomInsertion(delement *, int);
delement * createDNode(int, delement*);
void printDList(delement *);

int main()
{
    element *list;
    delement *dlist;

    initialize_Dlist(&dlist);
    /*printList(list);
    handleList(&list);*/

}

element * createNode(int val)
{
    element *node;

    node = (element *)malloc(sizeof(element));

    node->val = val;
    node->next = NULL;

    return node;
}

void printList(element *list)
{
    if(list != NULL)
    {
        printf("%d -> ", list->val);
        printList(list->next);
    }
    else
        printf("//\n");
}

void initialize_list(element **list)
{
    int size, val, choose;

    printf("How many elements? ");
    scanf("%d", &size);

    *list = NULL;
    
    
    srand(time(NULL));
    printf("\n[0] Sorted insertion \n[1] Head insertion\n[2] Bottom insertion\n[3] if you want to exit\nChoose: ");
    scanf("%d", &choose);
    fflush(stdin);
    switch (choose)
    {
        case 0:
            for (int i = 0; i < size; i++)
            {
                printf("Insert element value n.%d: %d\n", i+1, (val = rand() % 100 +1));
                *list = sortedInsertion(*list, val);
            }
            break;
            
        case 1:
            for (int i = 0; i < size; i++)
            {
                printf("Insert element value n.%d: %d\n", i+1, (val = rand() % 100 +1));
                *list = headInsertion(*list, val);
            }
            break;
            
        case 2:
            for (int i = 0; i < size; i++)
            {
                printf("Insert element value n.%d: %d\n", i+1, (val = rand() % 100 +1));
                *list = bottomInsertion(*list, val);
            }
            break;
            
        case 3:
            exit(0);
    }
}

void handleList(element **list)
{
    int choose, search;
    element *max;

    while(1)
    {
        printf("\n[0] Doubles odd \n[1] Delete elements divisible by 10\n[2] Search element\n[3] Insert even\n[4] Delete element\n[5] Search max\n[6] Search min\n[7] Quit\nChoose: ");
        scanf("%d", &choose);
        fflush(stdin);
        switch (choose)
        {
            case 0:
                doublesOdd(*list);
                printList(*list);
                break;
                
            case 1:
                *list = deleteTen(*list);
                printList(*list);
                break;
                
            case 2:
                printf("What element should I search? ");
                scanf("%d", &search);
                fflush(stdin);
                if(searchElement(*list, search) == 1)
                    printf("Found.\n");
                else
                    printf("Not found.\n");
                break;
                
            case 3:
                *list = insertEven(*list);
                printList(*list);
                break;
            
            case 4:
                printf("What element should I delete? ");
                scanf("%d", &search);
                fflush(stdin);
                printList(*list);
                printf("Delete element ...\n"), sleep(1);
                deleteElement(*list, search);
                printList(*list);
                break;
            
            case 5:
                if ((max = searchMax(*list)) != NULL)
                    printf("Max is %d.\n", max->val);
                else  
                    printf("List is empty");
                break;
            
            case 6:
                if ((max = searchMin(*list)) != NULL)
                    printf("Min is %d.\n", max->val);
                else  
                    printf("List is empty");
                break;

            case 7:
                exit(1);
        }
    }
}

element * sortedInsertion(element *list, int val)
{
    if(list == NULL)
        list = createNode(val);
    else
    {
        if(val > list->val)
            list->next = sortedInsertion(list->next, val);
        else
        {
            element *tmp;
            tmp = createNode(val);
            tmp->next = list;
            return tmp;        
        }
    }

    return list;
        
}

element * bottomInsertion(element *list, int val)
{
    if(list == NULL)
        list = createNode(val);
    else
        list->next = bottomInsertion(list->next, val);

    return list;
}

element * headInsertion(element *list, int val)
{
    
    element *tmp = createNode(val);
    tmp->next = list;

    return tmp;
}

void * doublesOdd(element *l)
{
    if(l != NULL)
    {
        if ((l->val % 2) != 0)
            l->val = l->val * 2;
        doublesOdd(l->next);    
    }
}

element * deleteTen(element *l)
{
    if(l != NULL)
    {
        
        if((l->val % 10) == 0)
        {
            l = l->next;
            l = deleteTen(l);
        }
        else
            l->next = deleteTen(l->next);
    }

    return l;
}

int searchElement(element *l, int val)
{
    int check = 0;

    if(l != NULL)
    {
        if(l->val == val)
            check = 1;
        else
            check = searchElement(l->next, val);
    }

    return check;
}

element * insertEven(element *l)
{
    if(l != NULL)
    {
        if ((l->val % 2) != 0)
        {
            element *tmp = createNode(l->val + 1);
            tmp->next = l->next;
            l->next = tmp;
            tmp->next = insertEven(tmp->next);
        }
        else
            l->next = insertEven(l-> next);
    }
    return l;
}

element * deleteElement(element * l, int val)
{
    if(l != NULL)
    {
        if(l->val == val)
            l = l->next;
        else
            l->next = deleteElement(l->next, val);
    }

    return l;
}

element * searchMax(element *l)
{
    element *tmp;
    if(l != NULL)
    {
        tmp = searchMax(l->next);
        if((tmp == NULL) || (tmp->val < l->val))
            tmp = l;
    }
    else
        tmp = NULL;

    return tmp;
}

element * searchMin(element *l)
{
    element *tmp;

    if(l != NULL)
    {
        tmp = searchMin(l->next);
        if((tmp == NULL) || (l->val < tmp-> val) )
            tmp = l;
    }
    else
        tmp = NULL;

    return tmp;
}

void initialize_Dlist(delement **l)
{
    int size, val, choose;

    printf("How many elements? ");
    scanf("%d", &size);

    *l = NULL;

    srand(time(NULL));
    printf("\n[0] Sorted insertion \n[1] Head insertion\n[2] Bottom insertion\n[3] if you want to exit\nChoose: ");
    scanf("%d", &choose);
    fflush(stdin);
    switch (choose)
    {
        case 0:
            for (int i = 0; i < size; i++)
            {
                printf("Insert element value n.%d: %d\n", i+1, (val = rand() % 100 +1));
                *l = dSortedInsertion(*l, val);
            }
            printDList(*l);
            break;
            
        case 1:
            for (int i = 0; i < size; i++)
            {
                printf("Insert element value n.%d: %d\n", i+1, (val = rand() % 100 +1));
                *l = dHeadInsertion(*l, val);
            }
            printDList(*l);
            break;
            
        case 2:
            for (int i = 0; i < size; i++)
            {
                printf("Insert element value n.%d: %d\n", i+1, (val = rand() % 100 +1));
                *l = dBottomInsertion(*l, val);
            }
            printDList(*l);
            break;
            
        case 3:
            exit(0);
    }
}

delement * createDNode(int val, delement *prev)
{
    delement *node;

    node = (delement *)malloc(sizeof(delement));
    node->val = val;
    node->next = NULL;
    node->prev = prev;

    return node;
}

delement * dBottomInsertion(delement *l, int val)
{
    if(l == NULL)
        l = createDNode(val, NULL);
    else
    {
        if(l->next == NULL)
            l->next = createDNode(val, l);
        else
            l->next = dBottomInsertion(l->next, val);
    }
    return l;       
}

delement * dSortedInsertion(delement *l, int val)
{
    if(l == NULL)
        l = createDNode(val, NULL);
    else
    {
        if (l->val > val)
        {
            delement *tmp = createDNode(val, l->prev);
            tmp->next = l;
            l->prev = tmp;
            return tmp;
        }
        else
            l->next = dSortedInsertion(l->next, val);   
    }

    return l;
}

delement * dHeadInsertion(delement *l, int val)
{
    delement *tmp;

    tmp = createDNode(val, NULL);
    tmp->next = l;

    return tmp;
}

void printDList(delement *l)
{
    if(l == NULL)
        printf("\\\n");
    else
    {
        printf("<- %d -> ", l->val);
        printDList(l->next);
    }
}