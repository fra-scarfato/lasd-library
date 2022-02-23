#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct element
{
    int priority;
    char name[26];
};

typedef struct element element;
void heapsort(element *, int);
void buildHeap(element *, int);
void heapify(element *, int, int);
int isFull(int);
void print_array(element *, int);
int left(int);
int right(int);
int parent(int);
void swap(element *, int, int);
void maximum(element *, int);
void inserting(element *, int *);
void extract_max(element *, int *);

int main()
{
    element *queue;
    int heap_size;

    printf("Quanti elementi vuoi inserire nella coda di priorità? ");
    scanf("%d", &heap_size);
    queue = (element *) malloc(100 * sizeof(element));
    srand(time(NULL));

    for (int i = 0; i < heap_size; i++)
    {
        fflush(stdin);
        printf("Inserisci il nome dell'elemento n. %d: ", i+1);
        scanf("%s", queue[i].name);
        fflush(stdin);
        printf("La priorità di '%s' sarà: "/*%d\n"*/,queue[i].name/*, (queue[i].priority = rand() % 100 +1)*/);
        scanf("%d", &queue[i].priority);
    }    

    printf("\nThis the queue.\n");
    print_array(queue, heap_size);
    heapsort(queue, heap_size);
    printf("\nThis is the heap tree sorted by heapsort\n");
    print_array(queue, heap_size);

    int choose;
    buildHeap(queue, heap_size);
    while(1)
    {
        printf("\n[0] if you want to insert element\n[1] if you want the element with the max priority\n[2] if you want to extract the element with max priority\n[3] if you want to exit\nChoose: ");
        scanf("%d", &choose);
        switch (choose)
        {
            case 0:
                if(isFull(heap_size) == 0)
                {
                    inserting(queue, &heap_size);
                    print_array(queue, heap_size);
                }
                else
                    printf("Queue is full. Extract the max.\n");
                break;
            
            case 1:
                maximum(queue, heap_size);
                break;
            
            case 2:
                extract_max(queue, &heap_size);
                print_array(queue, heap_size);
                break;
            
            case 3:
                exit(0);
        }
    }

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

void swap(element *array, int max, int min)
{
    element temp;

    temp = array[min];
    array[min] = array[max];
    array[max] = temp;
}

void print_array(element *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("[%d] %s", array[i].priority, array[i].name);
        printf("\n");
    }
    
}

int isFull(int heapSize)
{
    if (heapSize == 100)
        return 1;
    else
        return 0;  
}

void heapsort(element *queue, int heapSize)
{
    buildHeap(queue, heapSize);
    for (int i = heapSize - 1; i >= 1; i--)
    {
        swap(queue, 0, i);
        heapSize--;
        heapify(queue, 0, heapSize);
    }
}

void buildHeap(element *queue, int heapSize)
{
    for(int i = heapSize/2; i >= 0; i--)
        heapify(queue, i, heapSize);
}

void heapify(element *queue, int currentElement, int heapSize)
{
    int largest, lft, rgt;

    lft = left(currentElement);
    rgt = right(currentElement);

    if((lft < heapSize) && (queue[currentElement].priority < queue[lft].priority))
        largest = lft;
    else
        largest = currentElement;
    
    if ((rgt < heapSize) && (queue[largest].priority < queue[rgt].priority))
        largest = rgt;

    if(largest != currentElement)
    {
        swap(queue, largest, currentElement);
        heapify(queue, largest, heapSize);
    }  
}

void inserting(element *queue, int *heapSize)
{
    int i;

    (*heapSize)++;  //AGGIUNGO UN ELEMENTO QUINDI AUMENTO LA DIMENSIONE DEL HEAP
    //AGGIUNGO IL NUOVO ELEMENTO ALLA FINE COME ULTIMO ELEMENTO DEL HEAP NEL NUOVO INDICE (heapsize++) VUOTO
    printf("Inserisci il nome dell'elemento da inserire: ");
    scanf("%s", queue[(*heapSize)-1].name);
    fflush(stdin);
    printf("Inserisci la priorità di '%s': ", queue[(*heapSize)-1].name);
    scanf("%d", &queue[(*heapSize)-1].priority);

    //DOPO AVERLO INSERITO DEVO CONTROLLARE NEI PARENT SOPRA SE LE PROPRIETÀ DEL HEAP SONO RISPETTATE QUINDI VADO ALL'INSÙ
    i = (*heapSize)-1;  //INDICE DEL NUOVO ELEMENTO INSERITO
    while((parent(i) >= 0) && (queue[parent(i)].priority < queue[i].priority))  //SE NON SONO ANDATO AL DI SOPRA DELLA RADICE E SE IL PADRE DEL NUOVO NODO È MINORE (NON RISPETTA PROPRIETÀ HEAP)
    {
        swap(queue, i, parent(i));  //SCAMBIO PADRE E NODO
        i = parent(i);  //DOPO LO SCAMBIO IL NODO AVRÀ UN NUOVO INDICE OVVERO QUELLO DEL PADRE CON CUI SI È SCAMBIATO
    }   //VA AVANTI A CONTROLLARE TUTTI I NODI AL DI SOPRA FINCHÈ O NON ARRIVA ALLA RADICE OPPURE NON TROVA UN PARENT CHE HA PRIORITÀ MAGGIORE
}

void maximum(element *queue, int heapSize)
{
    printf("Element with max priority is: %s (%d).\n", queue[0].name, queue[0].priority);
}

void extract_max(element *queue, int *heapSize)
{
    element max;

    max = queue[0]; //SALVO IL MASSIMO ELEMENTO
    queue[0] = queue[(*heapSize)-1];    //METTO ULTIMO ELEMENTO NELLA RADICE CHE NON È OCCUPATA DA NESSUNO POICHÈ IL MAX È STATO ESTRATTO 
    (*heapSize)--;      //DIMINUISCO LA HEAPSIZE
    heapify(queue, 0, (*heapSize)-1);   //CHIAMO LA HEAPIFY SULLLA RADICE IN MODO CHE SI RISTABILISCA LA PROPRIETÀ DEL HEAP

    printf("Element with max priority EXTRACTED is: %s (%d).\n", max.name, max.priority);
}

//NEL CASO SI VOGLIA INCREMENTARE UNA SPECIFICA CHIAVE BASTA FARE UNA COSA SIMILE A QUANDO SI INSERISCE UN NUOVO NODO OVVERO CONTROLLO AL DI SOPRA SE
//LA PROPIRETÀ DI HEAP È ANCORA RISPETTATA

//NEL CASO IN CUI SI VOGLIA DECREMENTARE INVECE SI SEGUE UN APPROCCIO SIMILE A L'ESTRAZIONE DEL MASSIMO INFATTI SI DECREMENTA LA CHIAVE E POI SI
//CHIAMA UN HEAPIFY SUL NODO DECREMENTATO IN MODO DA CONTROLLARE SE LA PROPRIETÀ DI HEAP È RISPETTATA

//NEL CASO IN CUI VOGLIA ELIMINARE UN I-ESIMO ELEMENTO DEL HEAP, GLI ASSEGNO PRIORITÀ MASSIMA, LO PORTO ALLA ROOT E LO ESTRAGGO
//OPPURE GLI ASSEGNO UN VALORE MINORE DELL'ULTIMA FOGLIA, CHIAMO UNA HEAPIFY SUL NODO E DECREMENTO HEAPSIZE
