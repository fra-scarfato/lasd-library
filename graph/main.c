#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 20

typedef struct edge
{
    int key;
    int height;
    struct edge *next;

}edge;

typedef struct graph
{
    int nVer;
    edge **adj;

}graph;

void initializeGraph(graph **);
void insertVertex(graph **);
void insertEdge(graph **, int, int);
void printGraph(graph *);
edge * bottomInsertion(edge *, int);
void printList(edge *);
void handleGraph(graph **);
edge * createNode(int);
void deleteVertex(graph **, int);
void dfsGeneral(graph *);
void dfs(graph *, int, int *);
void bfsGeneral(graph *);
void bfs(graph *, int, int *);
void enqueue(int *, int);
int dequeue(int *);

int main()
{
    graph* g;

    initializeGraph(&g);
    handleGraph(&g);
}

void initializeGraph(graph **g)
{
    
    *g = (graph *)malloc(sizeof(graph));    

    printf("How many vertex do you want? ");
    scanf("%d", &((*g)->nVer));

    (*g)->adj = (edge **)malloc((*g)->nVer * sizeof(edge *));   //STRUTTURA VERA E PROPRIA OVVERO VETTORE DI PUNTATORI, I PUNTATORI SARANNO DELLE LISTE DI ADIACENZA
    
    for (int i = 0; i < (*g)->nVer; i++)
        (*g)->adj[i] = NULL;   //SETTO TUTTO A NULL ALL'INIZIO POICHÈ NON HO ARCHI
}

void insertVertex(graph **g)
{
    (*g)->nVer++;   //AUMENTO IL NUM DI VERTICI
    
    (*g)->adj = (edge **)realloc((*g)->adj, (*g)->nVer * sizeof(edge *));   //RIALLOCO PIU SPAZIO
    (*g)->adj[(*g)->nVer - 1] = NULL;   //SETTO A NULL IL NUOVO VERTICE
}

void insertEdge(graph **g, int u, int v)
{
    (*g)->adj[u] = bottomInsertion((*g)->adj[u], v);    //È UN INSERIMENTO ALLA FINE DELLA LISTA, IN QUESTO CASO IL PTR ALLA LISTA È LA LISTA DI ADIACENZA DI 
    //SI PUO FARE ANCHE CON WHILE E SCORRO LA LISTA
}

void printGraph(graph *g)
{
    printf("Graph has %d vertices.\n", g->nVer);
    for(int i = 0; i < g->nVer; i++)    //FOR SUI VERTICI (VETTORE)
    {
        printf("%d : ", i); //STAMPO IL VERTICE
        printList(g->adj[i]);   //E LA SUA LISTA DI ADIACENZA (SI PUO FARE CON WHILE)
    }
}

edge * bottomInsertion(edge *list, int val)
{
    if(list == NULL)
        list = createNode(val);
    else
        list->next = bottomInsertion(list->next, val);

    return list;
}

void printList(edge *e)
{
    if(e == NULL)
        printf("\\ \n");
    else
    {
        printf("%d -> ", e->key);
        printList(e->next);
    }
}

edge * createNode(int val)
{
    edge *node;

    node = (edge *)malloc(sizeof(edge));

    node->key = val;
    node->next = NULL;

    return node;
}

edge * deleteElement(edge * l, int val)
{
    if(l != NULL)
    {
        if(l->key == val)
            l = l->next;
        else
            l->next = deleteElement(l->next, val);
    }

    return l;
}

void deleteEdge(graph *g, int u, int v)
{
    g->adj[u] = deleteElement(g->adj[u], v);    //È UNA SEMPLICE ELIMINAZIONE DALLA LISTA DI ADIACENZA DI U IL VALORE V
    //PER FARLO ITERATIVAMENTE SERVE SALVARE IL PREV
}

void handleGraph(graph **g)
{
    int choose, u, v;

    printGraph(*g);
    while(1)
    {
        printf("\n[0] Insert vertex\n[1] Insert edge\n[2] Delete edge\n[3] Delete vertex\n[4] DFS\n[5] BFS\nChoose: ");
        scanf("%d", &choose);
        fflush(stdin);
        switch (choose)
        {
            case 0:
                printf("Insert vertex n.%d.\n", (*g)->nVer);
                insertVertex(&(*g));
                printGraph(*g);
                break;
                
            case 1:
                printf("Starter vertex: ");
                scanf("%d", &u);
                fflush(stdin);
                printf("Ended vertex: ");
                scanf("%d", &v);
                fflush(stdin);
                insertEdge(&(*g), u, v);
                printGraph(*g);
                break;
                
            case 2:
                printf("Starter vertex: ");
                scanf("%d", &u);
                fflush(stdin);
                printf("Ended vertex: ");
                scanf("%d", &v);
                fflush(stdin);
                deleteEdge(*g, u, v);
                printGraph(*g);
                break;
                
            case 3:
                printf("Delete vertex: ");
                scanf("%d", &u);
                deleteVertex(&(*g), u);
                printGraph(*g);
                break;

            case 4:
                dfsGeneral(*g);
                break;

            case 5:
                bfsGeneral(*g);
                break;
        }
    }

}

void deleteVertex(graph **g, int deleted)
{
    for (int i = 0; i < (*g)->nVer; i++)
        deleteEdge(*g, i, deleted);     //ELIMINO TUTTI GLI ARCHI IN CUI È COINVOLTO IL VERTICE DA ELIMINARE

    for (int i = deleted; i < (*g)->nVer - 1; i++)
        (*g)->adj[i] = (*g)->adj[i + 1];    //FACCIO UNO SHIFT A SINISTRA DEI VERTICI
    
    (*g)->nVer--;   //DECREMENTO IL NUMERO DI VERTICI

    (*g)->adj = (edge **)realloc((*g)->adj,(*g)->nVer * sizeof(edge));  //RIALLOCO IL GIUSTO SPAZIO
}

void dfsGeneral(graph *g) //PROSSIMO NODO DA VISITARE È CONNESSO CON UN ARCO AL NODO CHE STO VISITANDO E CHE NON HO ANCORA VISITATO E CHE ABBIA ARCHI CONNESSI A NODI NON VISISTATI
{
    int *aux;
    aux = (int *)calloc(g->nVer, sizeof(int));  //IN QUESTO VETTORE SALVO I VERTICI GIA VISITATI
    
    for (int i = 0; i < g->nVer; i++)
    {
        if (aux[i] == 0)    //SE NON È STATO ANCORA VISISTATO
        {
            printf("\n%d -> ", i);  //STAMPO
            dfs(g, i, aux);  //LO VISISTO
        }  
    }
    
}

void dfs(graph *g, int ind, int *aux)
{
    edge *tmp;
    aux[ind] = 1;   //STO VISITANDO IL NODO QUINDI SETTO 1

    for (tmp = g->adj[ind]; tmp != NULL; tmp = tmp->next)   //SCORRO GLI ARCHI DEL NODO CHE STO VISITANDO PER VEDERE SE POSSO VISITARE ALTRI NODI CONNESSI
    {
        if(aux[tmp->key] == 0)  //se trovo un nodo nella lista di adiacenza che non ho visistato
        {
            fflush(stdout);
            printf("%d -> ", tmp->key); //STAMPO
            dfs(g, tmp->key, aux);  //E LO VISITO
        }
    }
    
}

void bfsGeneral(graph *g)   //PROSSIMO NODO DA VISITARE È CONNESSO CON UN ARCO AL NODO VISITATO DA PIU TEMPO E CHE ABBIA ARCHI CHE LO CONNETTANO A NODI NON ANCORA VISITATI 
{
    int *aux;

    aux = calloc(g->nVer, sizeof(int)); //VETTORE PER VEDERE QUALI NODI HO VISITATO

    for(int i = 0; i < g->nVer; i++)    //VISITO TUTTI I VERTICI
    {
        if(aux[i] == 0) //SE VERTICE NON È STATO ANCORA VISISTATO
        {
            fflush(stdout);
            printf("\n%d -> ", i);
            bfs(g, i, aux); //VISITO
        }
    }
}

void bfs(graph *g, int i, int *aux)
{
    edge *tmp;
    int *queue;

    queue = calloc(MAX + 2, sizeof(int)); //IMPLEMENTO CODA PER SALVARE I VERTICI ADIACENTI AL NODO CHE STO VISITANDO
    queue[MAX + 1] = 1;
    enqueue(queue, i);  //METTO IN CODA IL NODO CHE STO VISITANDO

    while (queue[0] != 0)
    {
        i = dequeue(queue);     //DECODO UNO DEI NODI ACCODATI (ADIACENTI O SORGENTE NEL CASO DEL PRIMO ELEMENTO)
        aux[i] = 1;             //VISITO NODO
        for (tmp = g->adj[i]; tmp != NULL; tmp = tmp->next) //SCORRO LA LISTA DI ADIACENZA DEL NODO CHE STO VISITANDO
        {
            if(aux[tmp->key] != 1)  //SE I NODI DELLA LISTA DI ADIACENZA NON SONO STATI GIA VISISTATI
            {
                printf("%d -> ", tmp->key);
                enqueue(queue, tmp->key);   //ACCODO PER POI ANALIZZARE LA LORO LISTA DI ADIACENZA
                aux[tmp->key] = 1;      //VISITO
            }
        }
    }
    free(queue);
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

int checkExitGrade(graph *g, int i)
{
    int grade = 0;
    edge *tmp = g->adj[i];

    if(g->adj[i] != NULL)   //CERCO IL GRADO USCENTE
        grade = lengthList(tmp);    //OVVERO NELLA SUA LISTA DI ADIACENZA QUANTI NODI HA

    return grade;
}

int lengthList(edge *tmp)
{
    int length = 0;

    if(tmp != NULL)
        length = lengthList(tmp->next) + 1;

    return length;
}


int checkEntryGrade(graph *g, int v)
{
    int grade = 0;

    for (int i = 0; i < g->nVer; i++)   //CERCO IL GRADO ENTRANTE DI v
    {
        if (g->adj[i] != NULL)  //QUINDI CERCO NELLA LISTA DI ADIACENZA DI OGNI VERTICE SE v È PRESENTE
            grade += searchElement(g->adj[i], v);
    }   
}

int searchElement(edge *l, int val)
{
    int check = 0;

    if(l != NULL)
    {
        if(l->key == val)
            check = 1;
        else
            check = searchElement(l->next, val);
    }

    return check;
}

/*UN GRAFO È DETTO CONNESSO SE OGNI COPPIA DI VERTICI È COLLEGABILE TRAMITE UN PERCORSO
IL PESO DI UN CAMMINO TRA DUE VERTICI È DATO DALLA SOMMA DEI PESI DEGLI ARCHI CHE LO COSTITUISCONO
LO SHORTEST PATH È IL CAMMINO CON PESO MINIMO CHE COLLEGA V0 E VK, PER IL PRINCIPIO DI OTTIMALITÀ ANCHE QUALSIASI SOTTOCAMMINO CONTENUTO IN P
(PER ESEMPIO DA Vi A Vj) È ANCHE ESSO IL MINIMO PERCORSO CHE COLLEGA QUEI 2 VERTICI
SE PARTO DA s E VOGLIO ANDARE IN v, ESEGUENDO L'ALGORITMO OTTENGO
- d[v] = DISTANZA DA s A v LUNGO LO SP (SHORTEST PATH)
- n[v] = PREDECESSORE DEL NODO v LUNGO SP

SI USA TECNICA DEL RILASSAMENTO PER VALUTARE SE, UTILIZZANDO UN ALTRO NODO COME PREDECESSORE, SI PUÒ MIGLIORARE d[v]
- SE MIGLIORA, SI AGGIORNANO d[v] E n[V]
- SE NON MIGLIORA, NON SI FA NULLA

DIJKSTRA (DA u A v)
- INSIEME S: VERTICI DI CUI È STATO DETERMINATO LO SP, INIZIALMENTE VUOTO
- INSIEME S' = V-S (IN UNA CODA A PRIORITÀ)

SI INIZIA SELEZIONANDO RIPETUTAMENTE UN VERTICE u CON LA MINIMA STIMA DI CAMMINO MINIMO,
LO INSERIAMO IN S,
RILASSIAMO GLI ARCHI USCENTI DA U.
ALGORITMO TERMINA QUANDO S = V

For each vertice v in Grafo:                               // Inizializzazione
          dist[v] := infinito ;                                  // Distanza iniziale sconosciuta dalla sorgente a v  
          precedente[v] := non definita ;                             // Nodo precedente in un percorso ottimale
end for                                                    // dalla sorgente

dist[sorgente] := 0 ;                                        // Distanza dalla sorgente alla sorgente
Q := L'insieme di tutti i nodi nel Grafo ;                       // Tutti i nodi nel grafo sono non ottimizzati e quindi stanno in Q                                                                
      
while Q non è vuota:                                      // Loop principale
    u := estrai Minimo(Q) ;                                // Nodo iniziale per il primo caso
    rimuovi u da Q ;
          

    For each neighbour v di u:                          //Rilassamento
        alt := dist[u] + dist_tra(u, v) ;

        if alt < dist[v]:                               // questa condizione e' sempre false se v e' gia stato rimosso da Q
            dist[v] := alt ;
            precedente[v] := u ;                         
        end if
          
    end for
end while
      
return dist;

*/