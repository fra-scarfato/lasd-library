#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 100

//FIFO

void new_queue(int *);
int empty_queue(int *);
int full_queue(int *);
void enqueue(int *, int);
int dequeue(int *);
void print_queue(int *);
void delete_odd(int *);
void rewerse(int *);


int main()
{
    int *queue;

    srand(time(NULL));
    queue = calloc(MAX + 2, sizeof(int));
    new_queue(queue);
    print_queue(queue);
    printf("\nDelete odds\n");
    delete_odd(queue);
    rewerse(queue);
    print_queue(queue);

}

void new_queue(int *queue)
{
    int val, size;

    printf("How many elements? ");
    scanf("%d", &size);
    queue[0] = 0, queue[MAX + 1] = 1;
    for (int i = 0; i < size; i++)
    {
        printf("Insert n.%d: ", i+1);
        scanf("%d", &val);
        enqueue(queue, val);
    }   
}

int empty_queue(int *q)
{
    if(q[0] == 0)
        return 1;
    else 
        return 0;
}

int full_queue(int *q)
{
    if(q[0] == q[MAX + 1])
        return 1;
    else
        return 0;
}

void enqueue(int *q, int val)   //METTE IN CODA
{
    q[q[MAX+1]] = val;  //METTE L'ELEMENTO ALLA FINE
    if(q[0] == 0)       //SE LA CODA ERA VUOTA
        q[0] = 1;       //LA TESTA DIVENTA IL PRIMO ELEMENTO
    
    q[MAX+1] = (q[MAX + 1] % MAX) + 1;  //SI INCREMENTA CON IL MODULO IN MODO CHE SI POSSANO SOVRAPPORRE Q[0] E Q[MAX + 1] QUANDO LA CODA VIENE OCCUPATA TUTTA
}

int dequeue(int *q) //TOGLIE ELEMENTI DALLA TESTA
{
    int val;    

    val = q[q[0]];  //ESTRAE L'ELEMENTO IN TESTA
    q[0] = (q[0] % MAX) + 1;    //INCREMENTA L'INDICE DELLA TESTA 

    if(q[0] == q[MAX + 1])  //SE I DUE INDICI COINCIDONO, SIGNIFICA CHE LA LISTA È VUOTA QUINDI SI RESETTANO LE COND. INIZIALI
    {
        q[0] = 0;
        q[MAX + 1] = 1;
    }
    return val;
}

static void print_q(int *q)
{
    int val;

    if(empty_queue(q) == 0)
    {
        val = dequeue(q);
        printf("%d - ", val);
        print_q(q);
        enqueue(q, val);
    }
}

void rewerse(int *q)
{
    int val;
    if (empty_queue(q) == 0)
    {
        val = dequeue(q);
        rewerse(q);
        enqueue(q, val);
    }
    
}

void print_queue(int *q)
{
    print_q(q);
    rewerse(q);
}

void delete_odd(int *q)
{
    int val;

    if(empty_queue(q) == 0)
    {
        val = dequeue(q);
        delete_odd(q);
        if((val % 2) == 0)
            enqueue(q, val);
    }
}

