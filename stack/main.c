#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//STACK VIENE IMPLEMENTATO COME VETTORE CON SIZE MAX+1 POICHÈ NELL'ELEMENTO CON INDICE 0 C'È L'INDICE DELL'ULTIMO ELEMENTO INSERITO
//politica LIFO

void print_stack(int *);
int isFull(int *);
int isEmpty(int *);
void push(int *, int);
int pop(int *);
void new_stack(int *);
void delete_el(int *, int);

int main()
{
    int *stack, deleted;
    stack = (int *)calloc(MAX + 1, sizeof(int));

    new_stack(stack);
    print_stack(stack);
    printf("\nWhat element do u want to delete? ");
    scanf("%d", &deleted);
    delete_el(stack, deleted);
    print_stack(stack);

    return 0;
}

int isFull(int *stack)
{
    if(stack[0] == MAX)
        return 1;
    else 
        return 0;
}

int isEmpty(int *stack)
{
    if(stack[0] == 0)
        return 1;
    else 
        return 0;
}

void push(int *stack, int val)
{
    if(isFull(stack) == 1)
        printf("Stack full\n");
    else
    {
        stack[0]++;
        stack[stack[0]] = val; 
    }
}

int pop(int *stack)
{
    int val;

    if(isEmpty(stack) == 1)
        printf("Stack empty\n");
    else
    {
        val = stack[stack[0]];
        stack[0]--;
    }   
    return val; 
}

void new_stack(int *stack)
{
    int val, size;

    printf("How many elements? ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        printf("Insert n.%d: ", i+1);
        scanf("%d", &val);
        push(stack, val);
    }   
}

void print_stack(int *stack)
{
    int val;

    if((isEmpty(stack)) == 0)
    {
        val = pop(stack);
        printf("| %d |", val);
        print_stack(stack);
        push(stack, val);
    }
}

void delete_el(int *stack, int el)
{
    int val;

    if(isEmpty(stack) == 0)
    {
        val = pop(stack);
        delete_el(stack, el);
        if ((val != el))
            push(stack, val);
        
    }
}