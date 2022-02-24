typedef struct element
{
    int val;
    struct element *sx;
    struct element *dx;
}element;

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

typedef struct node
{
    struct node *prev;
    int val;
    struct node *next;
}node;

int checkABR(element *tree)    //FUNZIONE CHE VERIFICA SE UN ALBERO BINARIO È UN ABR
{
    int check = 1;  //VALORE DA RITORNARE SE È UGUALE 1 ALLORA È ABR ALTRIMENTI NO

    if(tree != NULL)    //PASSO INDUTTIVO
    {
        /*LE PRIME DUE CONDIZIONI ESPRIMONO:
        - SE ESISTE UN FIGLIO SINISTRO
        - E IL FIGLIO SINISTRO È MAGGIORE DEL VALORE DEL PADRE (NON RISPETTA PROPRIETÀ ABR)
        OPPURE (LE ALTRE 2 CONDIZIONI)
        - SE ESISTE FIGLIO DESTRO 
        - E IL FIGLIO DESTRO È MINORE DEL VALORE DEL PADRE (NON RISPETTA PROPRIETÀ ABR) */
        if(((tree->sx != NULL) && (tree->sx->val > tree->val)) || ((tree->dx != NULL)  && (tree->dx->val < tree->val))) 
            check = 0; //SE UNA DELLE COPPIE DI CONDIZIONI È VERIFICATA ALLORA L'ALBERO NON È UN ABR POICHÈ NON NE RISPETTA LE PROPRIETÀ
        else    //SE LE CONDIZIONI NON SONO VERIFICATE ALLORA PUÒ ANCORA ESSERE UN ABR
        {
            check = checkABR(tree->sx); //QUINDI CONTROLLO IL SOTTOALBERO SX
            check = checkABR(tree->dx); //E DX
        }
    }
    return check;
}

/*FUNZIONE CHE; 
- ELIMINA ELEMENTI NEGATIVI E MAGGIORI DEL NUMERO DI VERTICI DEL GRAFO (g->nv) DALLA DOUBLE LINKED LIST
- VERIFICA SE LA DOUBLE LINKED LIST È UN PERCORSO DEL GRAFO
- SE È UN PERCORSO LO ELIMINA DAL GRAFO 
*/
void foo(node **list, graph *g) //LA FUNZIONE DEVE CONTENERE TUTTE E 3 LE FUNZIONI QUINDI IMPLEMENTO FUNZIONI ITERATIVE
{
    node *tmp = *list;  //VARIABILE TMP PER SCORRERE LA LISTA
    node *toDelete;     //VARIABILE IN CUI SALVO I VALORI DA CANCELLARE
    int checkP = 1;     //VARIABILE PER CONTROLLARE SE LA LISTA È UN PERCORSO DEL GRAFO

    while(tmp != NULL)  //CICLO CHE ELIMINA ELMENTI NEGATIVI E MAGGIORI DI g->nv
    {
        if((tmp->val < 0) || (tmp->val > g->nVer)) //SE È UN NUMERO NEGATIVO O È MAGGIORE DI g->nv
        {
            
            if ((tmp->prev == NULL))
            {
                if(tmp->prev == NULL)   //CASO 1: ELEMENTO DA ELIMINARE È IL PRIMO ELEMENTO
                    *list = tmp->next;  //METTO IL PTR INIZIALE ALL'ELEMENTO SUCCESSIVO
            }
            else  //QUESTO ELSE COPRE TUTTI GLI ALTRI CASI
            {
              /*- tmp->next == NULL (ultimo elemento)
                - tmp->next != NULL && tmp->prev != NULL
                - tmp->next == NULL && tmp->prev == NULL (unico elemento della lista)*/
                tmp->prev->next = tmp->next;    //COLLEGO IL NODO PRECEDENTE DI TMP AL NODO SUCCESSIVO DI TMP IN MODO DA NON AVERE COLLEGAMENTI CON TMP
                tmp->next->prev = tmp->prev;    //IN ENTRAMBI I SENSI (SIA CON PREV DI TMP->NEXT SIA CON NEXT DI TMP->PREV)
            }
            toDelete = tmp;     //METTO IL VALORE DA CANCELLARE NELLA VARIABILE APPOSITA
            tmp = tmp->next;    //SCORRO LA LISTA
            free(toDelete);     //CANCELLO
        }
    }

    tmp = *list;    //PER RIPRISTINARE LA VARIABILE DI SCORRIMENTO DALL'INIZIO

    while((tmp != NULL) && (tmp->next != NULL) && (checkP != 0))    //CICLO CHE VERIFICA SE LA LISTA È UN PERCORSO DEL GRAFO
    {
        //USO LA FUNZIONE DI RICERCA (SOTTO È AGGIUNTA) SULLE LISTE E CERCO SE C'È UN ARCO CHE COLLEGA TMP->VAL E TMP->NEXT
        //VADO A CERCARE NELLA LISTA DI ADIACENZA DI TMP->VAL SE È PRESENTE TMP->NEXT->VAL
        if(search(g->adj[tmp->val], tmp->next->val) != 1)   
            checkP = 0; //SE NON TROVO TMP->NEXT->VAL NELLA LISTA DI ADIACENZA SIGNIFCA CHE NON È UN PERCORSO
        else
            tmp = tmp->next;    //ALTRIMENTI SCORRO LA LISTA
    }

    tmp = *list; //PER RIPRISTINARE LA VARIABILE DI SCORRIMENTO DALL'INIZIO

    if(checkP == 1) //SE LA LISTA È UN PERCORSO
    {
        while((tmp != NULL) && (tmp->next != NULL)) //CICLO PER ELIMINARE PERCORSO (ARCHI)
        {
            deleteEdge(g, tmp->val, tmp->next->val);    //ELIMINO ARCHI CHE FORMANO IL PERCORSO CON UNA FUNZIONE DEI GRAFI(SOTTO)
            tmp = tmp->next;    //SCORRO LISTA
        }
    }
}

int searchElement(node *l, int val)
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

void deleteEdge(graph *g, int u, int v)
{
    g->adj[u] = deleteElement(g->adj[u], v);    //È UNA SEMPLICE ELIMINAZIONE DALLA LISTA DI ADIACENZA DI U IL VALORE V
}

node * deleteElement(node * l, int val)
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