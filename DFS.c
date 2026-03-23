// C program illustrating DFS (recursive and non-recursive implementation)
// This implementation focuses on the recurcive implementation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERTICES 100


typedef struct Node
{  // data point
  int vertex;
  struct Node *next;
  
}Node;


// G = (V, E)
typedef struct
{
  int num_vertices;
  Node *vertices[MAX_VERTICES];
  
}Graph;



// CREATE A GRAPH OBJECT
Graph* createGraph(int numOfVertices)
{
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g-> num_vertices = numOfVertices;
  // loop through the list of pointers and nullify them
  for (int i =0 ; i < g->num_vertices; i++)
    {
      g->vertices[i] = NULL;
    }
  return g;
  
}


void addEdge(Graph* g, int src, int dest)
{
  Node *node = malloc(sizeof(Node));
  node->vertex = dest;
  node->next = g->vertices[src];
  g->vertices[src] = node;

  Node *node2 = malloc(sizeof(Node));
  node2->vertex = src;
  node2->next = g->vertices[dest];
  g->vertices[dest] = node2;
}


void dfs(Graph *g, int vertex, bool visited[])
{
  /*
    The idea of the algorithm is traversing.
    From the root node to the node and backtrack when their is no path.
   */

  visited[vertex] = true;
  printf("Visited:\t%d\n", vertex);
  Node *neighbour = g->vertices[vertex];
  while(neighbour != NULL)
    {
      if (!visited[neighbour->vertex])
	dfs(g, neighbour->vertex, visited);
      neighbour = neighbour -> next;
     }
}

void dfs_start(Graph *g ,int num)
{
  bool visited[MAX_VERTICES] = {false };
  dfs(g, num, visited);
}



int main()
{
  
  Graph* g = createGraph(6);

  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 3);
  addEdge(g, 1, 4);
  addEdge(g, 2, 5);

  printf("DFS starting from vertex 0:\n");
  dfs_start(g, 0);

  return 0;
}
