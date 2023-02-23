#include <stdio.h>

#define TRUE    1
#define FALSE   0

typedef int bool;

/*---------------------------------
 * Rotinas de Fila
 *---------------------------------*/
#define QUEUESIZE       1000

typedef struct {
        int q[QUEUESIZE+1];		/* body of queue */
        int first;                      /* position of first element */
        int last;                       /* position of last element */
        int count;                      /* number of queue elements */
} queue;

void init_queue(queue *q);
void enqueue(queue *q, int x);
int dequeue(queue *q);
int empty(queue *q);
void print_queue(queue *q);


/*---------------------------------
 * Rotinas de Grafo
 *---------------------------------*/
#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

typedef struct {
	int edges[MAXV+1][MAXDEGREE];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;

void initialize_graph(graph *g);
void read_graph(graph *g, bool directed);
void insert_edge(graph *g, int x, int y, bool directed);
void delete_edge(graph *g, int x, int y, bool directed);
void print_graph(graph *g);

/*---------------------------------
 * Percurso no Grafo
 *---------------------------------*/

bool processed[MAXV];	/* which vertices have been processed */
bool discovered[MAXV];  /* which vertices have been found */
int parent[MAXV];	/* discovery relation */

bool finished = FALSE;	/* if true, cut off search immediately */

void initialize_search(graph *g);
void bfs(graph *g, int start);
void dfs(graph *g, int v);
void find_path(int start, int end, int parents[]);

/*---------------------------------
 * Exemplo de Percurso no Grafo
 *---------------------------------*/

void process_vertex(int v)
{
	printf("processed vertex %d\n",v);
}

void process_edge(int x, int y)
{
	if (parent[x] == y)
        	printf("processed tree edge (%d,%d)\n",x,y);
	else
		printf("processed back edge (%d,%d)\n",x,y);
}

bool valid_edge(int e)
{
        return (TRUE);
}

int main(void)
{
	graph g;
	int i;

	read_graph(&g,FALSE);
	print_graph(&g);

	initialize_search(&g);
	dfs(&g,1);

	printf ("\nparent = [");
	for (i=1; i< g.nvertices; i++)
		printf ("%d,", parent[i]);
	printf ("%d]\n", parent[g.nvertices]);

    for (i=1; i<=g.nvertices; i++)
        find_path(1,i,parent);
    
    printf("\n");
	return 0;
}

/*---------------------------------
 * Implementacao Rotinas de Fila
 *---------------------------------*/

void init_queue(queue *q)
{
        q->first = 0;
        q->last = QUEUESIZE-1;
        q->count = 0;
}

void enqueue(queue *q, int x)
{
        if (q->count >= QUEUESIZE)
		printf("Warning: queue overflow enqueue x=%d\n",x);
        else {
                q->last = (q->last+1) % QUEUESIZE;
                q->q[ q->last ] = x;    
                q->count = q->count + 1;
        }
}

int dequeue(queue *q)
{
        int x = 0;

        if (q->count <= 0) printf("Warning: empty queue dequeue.\n");
        else {
                x = q->q[ q->first ];
                q->first = (q->first+1) % QUEUESIZE;
                q->count = q->count - 1;
        }

        return(x);
}

int empty(queue *q)
{
        if (q->count <= 0) return (TRUE);
        else return (FALSE);
}

void print_queue(queue *q)
{
        int i;

        i=q->first; 
        
        while (i != q->last) {
                printf("%c ",q->q[i]);
                i = (i+1) % QUEUESIZE;
        }

        printf("%2d ",q->q[i]);
        printf("\n");
}

/*---------------------------------
 * Implementacao Rotinas de Grafo
 *---------------------------------*/

void initialize_graph(graph *g)
{
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
}

void read_graph(graph *g, bool directed)
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y;			/* vertices in edge (x,y) */

	initialize_graph(g);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d",&x,&y);
		insert_edge(g,x,y,directed);
	}
}

void insert_edge(graph *g, int x, int y, bool directed)
{
	if (g->degree[x] > MAXDEGREE)
	    printf("Warning: insertion(%d,%d) exceeds max degree\n",x,y);

	g->edges[x][g->degree[x]] = y;
	g->degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,TRUE);
	else
		g->nedges ++;
}


void delete_edge(graph *g, int x, int y, bool directed)
{
	int i;				/* counter */

	for (i=0; i<g->degree[x]; i++) 
		if (g->edges[x][i] == y) {
			g->degree[x] --;
			g->edges[x][i] = g->edges[x][g->degree[x]];

			if (directed == FALSE)
				delete_edge(g,y,x,TRUE);

			return;
		}

	printf("Warning: deletion(%d,%d) not found in g.\n",x,y);
}

void print_graph(graph *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=0; j<g->degree[i]; j++)
			printf(" %d",g->edges[i][j]);
		printf("\n");
	}
}

/*-------------------------------------------
 * Implementacao Rotinas de Percurso no Grafo
 *-------------------------------------------*/

void initialize_search(graph *g)
{
        int i;                          /* counter */

        for (i=1; i<=g->nvertices; i++) {
                processed[i] = discovered[i] = FALSE;
                parent[i] = -1;
        }
}

void bfs(graph *g, int start)
{
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int i;				/* counter */

	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;

	while (empty(&q) == FALSE) {
		v = dequeue(&q);
		process_vertex(v);
		processed[v] = TRUE;
		for (i=0; i<g->degree[v]; i++) 
		    if (valid_edge(g->edges[v][i]) == TRUE) {
			if (discovered[g->edges[v][i]] == FALSE) {
				enqueue(&q,g->edges[v][i]);
				discovered[g->edges[v][i]] = TRUE;
				parent[g->edges[v][i]] = v;
			}
			if (processed[g->edges[v][i]] == FALSE) 
				process_edge(v,g->edges[v][i]);
		    }
	}
}

void dfs(graph *g, int v)
{
	int i;				/* counter */
	int y;				/* successor vertex */

	if (finished) return;		/* allow for search termination */

	discovered[v] = TRUE;
	process_vertex(v);

	for (i=0; i<g->degree[v]; i++) {
		y = g->edges[v][i];
		if (valid_edge(g->edges[v][i]) == TRUE) {
			if (discovered[y] == FALSE) {
				parent[y] = v;
				dfs(g,y);
			} else 
				if (processed[y] == FALSE)
					process_edge(v,y);
		}
		if (finished) return;
	}

	processed[v] = TRUE;
}


void find_path(int start, int end, int parents[])
{
	if ((start == end) || (end == -1))
		printf("\n%d",start);
	else {
		find_path(start,parents[end],parents);
		printf(" %d",end);
	}
}
