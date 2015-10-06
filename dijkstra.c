//
//  main.c
//  test
//
//  Created by David Whipple on 10/29/13.
//  Copyright (c) 2013 David Whipple. All rights reserved.
//


/* This is the implementation of Dijkstra's Algorithm for finding the minimum */
/* distance from one source node to every other node in a graph               */
/*                                                                            */
/*  Date	Author		Description	                              */
/*  ------------------------------------------------------------------------- */
/*  10/04/2013	David Whipple	Initial Code, Taken from Foundations of       */
/*                              Computer Science, pg. 502-512                 */
/*                                                                            */
/* This Algorithm finds the Shortest Path if we have a graph with distance    */
/* labels on the edges.  The shortest path from source node s to destination  */
/* node d.                                                                    */
/*                                                                            */
/* It uses balanced partially ordered trees (POT's). It is a binary tree with */
/* priorities on the nodes, where:                                            */
/*                                                                            */
/*      1. priority of a node >= priority of it's children                    */
/*      2. we actually maintain a balanced POT                                */
/*      3. embedded into a single array                                       */
/*                                                                            */
/*   POT Operations                                                           */
/*     - insert(), delete()                                                   */
/*     - bubbleUp()                                                           */
/*     - bubbleDown()                                                         */
/*                                                                            */
/* It is O(log n) with a balanced POT                                         */
/*                                                                            */
/*  Algorithm is as follows:                                                  */
/*     - We maintain a set of "settled" nodes for which we know the           */
/*       mininum distance.                                                    */
/*     - For an "unsettled" node v, find a path through settled nodes that    */
/*       ends with a jump to the unsettled v.                                 */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* Data Structures                                                            */
/*    GRAPH: table of nodes with adjanency list of edges.                     */
/*                                                                            */
/*                                                                            */
/*         dist    |  succs.    | toPOT      Nodes                            */
/*       ---------------------------------   -----                            */
/*   0   -         -            -        -   typedef struct {                 */
/*   1   -         -            -        -     float dist<---min. distance to */
/*       -         -            -        -                 source             */
/*       -         -            -        -     LIST successors<---adj. list   */
/*       -         -            -        -     POTNODE toPOT<--index into POT */
/*       -         -            -        -   } GRAPH[MAX]                     */
/*   u   -         -            -   a    -                                    */
/*       -         -            -        -   Edges                            */
/*       -         -            -        -   -----                            */
/*       -         -            -        -   typedef struct CELL *LIST;       */
/*       -         -            -        -   struct CELL {                    */
/*       -         -            -        -     NODE nodeName<-Index of NODE   */
/*   n-1 -         -            -        -     float nodeLabel<-edge distance */
/*       ---------------------------------     LIST next; <- next edge        */
/*                                           };                               */
/*                                                                            */
/*                                                                            */
/*                                        --------                            */
/*                                        - Laie -                            */
/*                                        --------                            */
/*                                           /                                */
/*                                          /                                 */
/*                                    ----------            -----------       */
/*                                    -Wahiawa -            - Kaneohe -       */
/*                                    ----------            -----------       */
/*                                       |                                    */
/*                                       |                                    */
/*                                    ----------            -----------       */
/*                                    |Pearl                                  */
/*                                       |                                    */
/*                                    ----------            -----------       */

#include <stdio.h>

#define PI 3.14159
#define TRUE 1
#define FALSE 0
#define MAX 100  /* Max NODES */
#define INFTY -1
#define MYDEBUG 1

typedef int BOOLEAN;
typedef int NODE;
typedef int POTNODE;
typedef int IPTUPLE;

typedef struct CELL *LIST; /* A LIST is a pointer to a CELL */
struct CELL {
    NODE nodeName;         /* index of next node */
    float nodeLabel;       /* edge distance      */
    LIST next;             /* next edge          */
};

typedef NODE POT[MAX+1];

/*  This is the GRAPH */
typedef struct {
    float distance;        /* mininum distance from source */
    LIST successors;       /* adjacency list               */
    POTNODE toPOT;         /* next edge                    */
} GRAPH[MAX];

float priority(POTNODE a, GRAPH G, POT P)
{
    return G[P[a]].distance;
}
/**************************************************************/
/*	 	Laie Kaneohe Honolulu PearlCity Maili Wahiawa */
/* Laie 	0 	1 	0 	0 	0 	1     */
/* Kaneohe 	1 	0 	1 	0 	0 	0     */
/* Honolulu 	0 	1 	0 	1 	0 	0     */
/* PearlCity 	0 	0 	1 	0 	1 	1     */
/* Maili 	0 	0 	0 	1 	0 	1     */
/* Wahiawa 	1 	0 	0 	1 	1 	0     */
/**************************************************************/
void load_graph(GRAPH G)
{
   G[0].
}

void print_graph(GRAPH G)
{
}


/* Function to swap to nodes of a partially ordered tree */
void swap(POTNODE a, POTNODE b, GRAPH G, POT P)
{
    NODE temp; /* used to swap POT nodes */
    
    if (MYDEBUG) printf("Entering swap.\n");
    temp = P[b];
    P[b] = P[a];
    P[a] = temp;
    G[P[a]].toPOT = a;
    G[P[b]].toPOT = b;
    if (MYDEBUG) printf("Exiting swap.\n");
}

/* Initialize the Graph */
void initialize(GRAPH G, POT P, int *pLast)
{
    int i; /* we use i as both a graph and a tree node */
    if (MYDEBUG) printf("Entering initialize.\n");
    for (i = 0; i < MAX; i++) {
        G[i].distance = INFTY;
        G[i].toPOT = i+1;
        P[i+1] = i;
    }
    G[0].distance = 0;
    (*pLast) = MAX;
    if (MYDEBUG) printf("Exiting initialize.\n");
}


void bubbleUp(POTNODE a, GRAPH G, POT P)
{
    if (MYDEBUG) printf("Entering bubbleUP.\n");
    if ((a > 1) &&
        (priority(a, G, P) < priority(a/2, G, P))) {
        swap(a, a/2, G, P);
        bubbleUp(a/2, G, P);
    }
    if (MYDEBUG) printf("Exiting bubbleUp.\n");
}
void bubbleDown(POTNODE a, GRAPH G, POT P, int last)
{
    POTNODE child;
    if (MYDEBUG) printf("Entering bubbleDown.\n");
    child = 2*a;
    if (child < last &&
        priority(child+1, G, P) < priority(child, G, P))
        ++child;
    if (child <= last &&
        priority(a, G, P) > priority(child, G, P)) {
        swap(a, child, G, P);
        bubbleDown(child, G, P, last);
    }
    if (MYDEBUG) printf("Exiting bubbleDown.\n");
}

void Dijkstra(GRAPH G, POT P, int *pLast)
{
    NODE u, v; /* v is the node we select to settle */
    LIST ps; /* ps runs down the list of successors of v;
              u is the successor pointed to by ps */
    if (MYDEBUG) printf("Entering Dijkstra.\n");
    initialize(G, P, pLast);
    while ((*pLast) > 1) {
        v = P[1];
        swap(1, *pLast, G, P);
        --(*pLast);
        bubbleDown(1, G, P, *pLast);
        ps = G[v].successors;
        while (ps != NULL) {
            u = ps->nodeName;
            if (G[u].distance > G[v].distance + ps->nodeLabel) {
                G[u].distance = G[v].distance + ps->nodeLabel;
                bubbleUp(G[u].toPOT, G, P);
            }
            ps = ps->next;
        }
    }
}

int main(int argc, const char * argv[])
{

    GRAPH graph;
    POT potNodes;
    POTNODE last;  /* index of the last node of the POT */
    
    if (MYDEBUG) printf("Entering main.\n");
    Dijkstra(graph, potNodes, &last);

    printf("Hello, World!\n");
    
    return 0;
}


