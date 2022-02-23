#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void insertion_sort();
int insert_size();
void create_array(int *,int);
void insertion(int *,int);
void print_array(int *,int);

void heap_sort();
void swap(int *, int, int);
void build_heap(int *, int, int *);
void heapify(int *, int, int *);
int left(int);
int right(int);
int parent(int);
void heap(int *,int);

int main(){
    char choice[4];
    
    printf("Welcome in the sorting program.\nSelect yout sort type.\n[I]\n[H]\n");
    scanf("%s",choice);

    
    if(strcmp(choice,"I") == 0)
        insertion_sort();
    if(strcmp(choice,"H") == 0)
        heap_sort();
    
}


//GENERIC FUNCTIONS

int insert_size()
{
    int n;

    do{
        printf("How many number do you want? ");
        scanf("%d",&n);
        
        if(n < 0 ||  n == 0)
            printf("Choose right number\n");

    }while(n < 0 ||  n == 0);
    return n;
}

void create_array(int *array, int n)
{

    for(int i=0; i<n; i++)
    {
        printf("Select element n.%d\n",i);
        scanf("%d",&array[i]);
        fflush(stdin);
    }
}

void print_array(int *array, int n)
{
    printf("I'm printing the array . . .\n");
    sleep(1);
    for (int i = 0; i < n; i++)
        printf("[ %d ] ", array[i]);

    printf("\n");
}


//INSERTION SORT

void insertion_sort()
{
    int n;
    int *array;

    
    n = insert_size();
    array = (int *)calloc(n, sizeof(int));
    create_array(array,n);
    print_array(array,n);
    printf("Sorting array . . . \n");
    sleep(2);
    insertion(array,n);
    print_array(array, n);
}

void insertion(int *array, int n)   //O(n^2) NEL CASO PEGGIORE POICHÈ N-1 CONFRONTI PER UN SINGOLO NUMERO, ESSENDO N I NUMERI
{
    int temp;
    int next;
    int current;

    for(next = 1; next < n; next++)
    {
        temp = array[next];     //Elemento da confrontare e da spostare
        current = next-1;       //Indice per confrontare temp con elementi precedenti
        while((current >= 0) && (array[current] > temp))    //Se rispetta le condizioni significa che uno degli elementi precedenti di temp è maggiore di temp
        {
            array[current+1] = array[current];      //Duplico il valore maggiore di temp un posto in avanti 
            current--;                              //Torno indietro per verificare se c'è qualche altro elemento maggiore di temp da spostare in avanti
        }
        array[current+1] = temp;    //Se non ci sono altri elementi, metto il temp al suo posto
    }
}


//HEAP SORT

void heap_sort()        //NODO PADRE SEMPRE MAGG O UGUALE DEI NODI FIGLIO
{
    int array_size;
    int *array;

    array_size = insert_size();
    array = (int *)calloc(array_size, sizeof(int));
    create_array(array,array_size);
    print_array(array,array_size);
    printf("Sorting array . . . \n");
    sleep(2);
    heap(array,array_size);
    print_array(array,array_size);    

}

int right(int i)
{
    return 2*i+2;
}

int left(int i)
{
    return 2*i+1;
}

int parent(int i)
{
    return (i-1)/2;
}

void swap(int *array, int max, int min)
{
    int temp;

    temp = array[min];
    array[min] = array[max];
    array[max] = temp;
}

void heap(int *array, int array_size)  //HEAPSORT O(n * log n)
{
    int heap_size;

    build_heap(array,array_size,&heap_size);
    for (int i = array_size-1; i >= 1; i--)
    {
        swap(array, 0, i);      //SCAMBIA POICHE' LA RADICE È SEMPRE IL NUMERO MAGGIORE PER LE PROPRIETÀ DELL'HEAP E L'ULTIMO ELEMENTO È IL MINORE
        heap_size--;            //POICHÈ L'ULTIMO ELEMENTO (IL MAGGIORE) VENGA ESCLUSO DAL PROSSIMO HEAPIFY
        heapify(array,0,&heap_size);    //HEAPIFY SUL RESTANTE HEAP
    }
    

}

void build_heap(int *array, int array_size, int *heap_size) //FA N CHIAMATE A HEAPIFY QUINDI O(n) * O(log n) = O(n * log n)
{
    *heap_size = array_size;
    
    for (int i = array_size/2; i >= 0; i--)     //ARRAYSIZE/2 POICHE' PARTE DAL PRIMO DELLE FOGLIE, VISTO CHE HEAPIFY PER LE FOGLIE È INUTILE POICHE LAVORA DALL'ALTO AL BASSO
        heapify(array, i, heap_size);           
    
}

void heapify(int *array, int i, int *heap_size) //O(h) OVVERO O(log n)
{
    int lt, rt, largest;

    lt = left(i);       //FIGLIO SINISTRO DELL INDICE I
    rt = right(i);      //FIGLIO DESTRO DELL INDICE I

    if((lt < *heap_size) && (array[lt] > array[i]))     //CONTROLLO SE L'INDICE DEL FIGLIO SINISTRO ESISTE (lt < heapsize?) E SE ESISTE CONTROLLO SE IL FIGLIO È MAGGIORE DEL PADRE
        largest = lt;   //SE IL FIGLIO SX È MAGGIORE DEL PADRE SALVO IL SUO INDICE "lt" COME "IL PIU GRANDE"
    else
        largest = i;    //SE NON SONO RISPETTATE LE CONDIZIONI INIZIALIZZO "IL PIU GRANDE" COME "i" POICHE' O NON ESISTE IL FIGLIO SX OPPURE IL NODO CON INDICE I È MAGGIORE

    if((rt < *heap_size) && (array[rt] > array[largest]))   //STESSI CONTROLLI PER IL FIGLIO DESTRO
        largest = rt;   //SE FIGLIO DX È MAGG DI "PIU GRANDE" (CHE POTREBBE ESSERE NODO I O FIGLIO SX) 

    if(largest != i)    //SE "IL PIU GRANDE" È UNO DEI FIGLI
    {
        swap(array,largest,i);  //SWAPPO IL FIGLIO CON IL PADRE
        heapify(array,largest,heap_size);   //FACCIO UN HEAPIFY NELL SOTTOALBERO DEL FIGLIO PER VEDERE SE HO CAMBIATO QUALCOSA CON QUESTO SWAP
    }

}





