#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int val;
    struct node *sx;
    struct node *dx;
}node;

int isEmpty(node *);
int root(node *,int *);
node * leftNode(node *);
node * rightNode(node *);
void initializeTree(node **);
node * createNode(int);
void insertNode(node **, int);
void preorderVisit(node *);
void orderVisit(node *);
void postorderVisit(node *);
void printTree(node *);
node * searchMinNode(node *);
void handleTree(node **);
int search(node *, int);
int searchMin(node *);
node * searchMinNode(node *);
void deleteNode(node **, int);

int main()
{
    node *tree;
    int del;

    initializeTree(&tree);
    printTree(tree);
    handleTree(&tree);
}

int isEmpty(node *t)
{
    int tmp;

    if(t == NULL)
        tmp = 1;
    else
        tmp = 0;
    return tmp;
}

int root(node *t, int *valRoot)
{
    int check = 0;

    if(isEmpty(t) == 0)
    {
        *valRoot = t->val;
        check = 1;
    }
    return check;
}

node * leftNode(node *t)
{
    node *tmp = NULL;

    if(isEmpty(t) == 0)
        tmp = t->sx;
    return tmp;
}

node * rightNode(node *t)
{
    node *tmp = NULL;

    if(isEmpty(t) == 0)
        tmp = t->dx;
    return tmp;
}

void initializeTree(node **t)
{
    int size, val; 

    srand(time(NULL));
    *t = NULL;
    printf("How many elements? ");
    scanf("%d", &size);

    if(size == 0)
        printf("Empty tree.\n");
    else
    {
        for(int i = 0; i < size; i++)
        {
            printf("Insert element %d: %d\n", i+1, (val = rand() % 100 + 1));
            insertNode(&(*t), val);                   //CON *l mando lista* l in pasto a insertBottom, invece con &(*l) manderei il doppio ptr
        }
    }
}

node * createNode(int val)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->val = val;
    tmp->dx = NULL;
    tmp->sx = NULL;

    return tmp;
}

void insertNode(node **t, int val)  //INSERIMENTO SECONDO LA PROPRIETÀ DEGLI ABR QUINDI IL FIGLIO SX DI UN NODO x È SEMPRE MINORE, IL FIGLIO DX È SEMPRE MAGGIORE
{
    if(*t == NULL)
        *t = createNode(val);   //UNA VOLTA ARRIVATO AL SUO POSTO SI CREA IL NODO
    else
    {
        if(val > (*t)->val) //SE VOGLIO INSERIRE VALORE MAGGIORE VADO A DX
            insertNode(&((*t)->dx), val);
        else
            insertNode(&((*t)->sx), val);   //SE VOGLIO INSERIRE VAL SX VADO A SX
    }
}

void preorderVisit(node *t)     //SI PARTE DALLA ROOT E SI SCENDE VERSO SX FINO ALLA FOGLIA, UNA VOLTA ARRIVATI ALLA FOGLIA SI RISALE AL PADRE E SI VA A DX
{
    if(t != NULL)
    {
        printf("%d -> ", t->val);
        preorderVisit(t->sx);
        preorderVisit(t->dx);
    }
}

void orderVisit(node *t)    //SI SCENDE A SX FINO ALLA FOGLIA. SI PARTE A STAMPARE DALLA FOGLIA SX (MINIMO), 
{                           //SI RISALE AL PADRE E SI STAMPA A DX. UNA VOLTA TERMINATO IL SOTTOALB SX SI STAMPA ROOT E SI FA LA STESSA COSA CON IL DX 
    if(t != NULL)
    {
        orderVisit(t->sx);
        printf("%d -> ", t->val);
        orderVisit(t->dx);
    }
}

void postorderVisit(node *t)    //SI STAMPANO LE FOGLIE DEL SOTTOALB SX, SI RISALE (NON SI ARRIVA ALLA ROOT), UNA VOLTA ARRIVATI AL FIGLIO SX DELLA ROOT
{                               //SI STAMPANO LE FOGLIE DEL SOTTOALB DX E SI RISALE FINO ALLA ROOT
    if(t != NULL)
    {
        postorderVisit(t->sx);
        postorderVisit(t->dx);
        printf("%d -> ", t->val);
    }
}

void printTree(node *t)
{
    int choose;

    
    printf("\n[0] Preorder visit\n[1] Order visit\n[2] Postorder visit\n[3] if you want to exit\nChoose: ");
    scanf("%d", &choose);

    switch (choose)
    {
        case 0:
            preorderVisit(t);
            break;
            
        case 1:
            orderVisit(t);
            break;

        case 2:
            postorderVisit(t);
            break;

        case 3:
            exit(1);
    }
}

int search(node *t, int val)
{
    int found = 0;

    if(t != NULL)       //RICERCA ABR
    {
        if(val == t->val)   //SE HO TROVATO VALORE
            found = 1;
        else if(val > t->val)   //SE VALORE È MINORE DEL NODO ANALIZZATO VADO A SX
            found = search(t->dx, val);
        else
            found = search(t->sx, val); //SE MAGGIORE VADO A DX
    }  
    return found;
}

void handleTree(node **t)
{
    int choose, min;

    while(1)
    {
        printf("\n[0] Search minimum\n[1] Search element\n[2] Delete node\n[3] if you want to exit\nChoose: ");
        scanf("%d", &choose);

        switch (choose)
        {
            case 0:
                min = searchMin(*t);
                printf("Minimum is %d.\n", min);
                break;
                
            case 1:
                printf("Search element: ");
                scanf("%d", &min);
                if(search(*t, min) == 1)
                    printf("Found.\n");
                else
                    printf("Not found.\n");
                break;

            case 2:
                printf("Delete element: ");
                scanf("%d", &min);
                deleteNode(&(*t), min);
                printTree(*t);
                break;

            case 3:
                exit(1);
        }
    }
}

int searchMin(node *t)  //IL MINIMO È ALL'ESTREMA SINISTRA QUINDI VADO A SX FINO ALLA FOGLIA SX
{
    int min;

    if(t != NULL)
    {
        if(t->sx != NULL)   //SE IL NODO ALL'ESTREMA SINISTRA NON HA FIGLIO SX SIGNIFICA CHE È IL MINIMO
            min = searchMin(t->sx);
        else
            min = t->val;   //SE HA ANCORA NODI A SINISTRA, CONTINUO A SCENDERE A SX
    }

    return min;
}

node * searchMinNode(node *t)
{
    node *min = NULL;

    if(t != NULL)
    {
        if(t->sx != NULL)
            min = searchMinNode(t->sx);
        else
            min = t;
    }

    return min;
}

void deleteNode(node **t, int val)
{
    if(*t != NULL)
    {
        if(val < (*t)->val) //SE VALORE DA ELIMINARE È MINORE DEL NODO ANALIZZATO
            deleteNode(&((*t)->sx), val);   //SCENDO A SX
        else if(val > (*t)->val)  //SE VALORE DA ELIMINARE È MAGGIORE 
            deleteNode(&((*t)->dx), val);   //SCENDO A DX
        else    //SE HO TROVATO IL NODO
        {
            if(((*t)->dx == NULL) && ((*t)->sx == NULL))    //CASO 1 = È UNA FOGLIA
            {
                free(*t);   //LO ELIMINO SEMPLICEMENTE
                *t = NULL;
            }
            else if(((*t)->dx != NULL) && ((*t)->sx != NULL))   //CASO 2 = HA ENTRAMBI SOTTOALBERI NON NULLI
            {
                (*t)->val = searchMin((*t)->dx);    //CERCA IL MINIMO NEL SOTTOALBERO DX
                deleteNode(&((*t)->dx), (*t)->val); //QUINDI ELIMINA IL RIMANENTE NODO CON IL MINIMO DENTRO
            }
            else if(((*t)->dx == NULL) || ((*t)->sx == NULL))   //CASO 3: SOLO SE UNO DEI SOTTOALBERI È VUOTO
            {
                node *tmp;
                
                if((*t)->dx == NULL)    //SOTTOALBERO DX VUOTO
                {
                    tmp = (*t)->sx; //TMP MI SERVE PER POI DEALLOCARE LO SPAZIO DI MEMORIA DELL'ALBERO SX PERCHÈ AVREI 2 PTR ALLO STESSO ELEMENTO
                    *t = (*t)->sx;  //IL SOTTOALBERO SX SOSTITUISCE IL NODO DA CANCELLARE
                }
                else if((*t)->sx == NULL)   //SOTTOALBERO SX VUOTO
                {
                    tmp = (*t)->dx;
                    *t = (*t)->dx;  //IL SOTTOALBERO DX SOSTITUISCE IL NODO DA CANCELLARE
                }
                free(tmp);
            }
        }
    }
}
