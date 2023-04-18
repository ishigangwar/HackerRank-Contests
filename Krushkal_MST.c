#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct  {
    int u, v, m, w;
} Arco;

int menorArco( Arco * arcos, int M ) {
    int menor, i;
    menor = -1;
    for (i = 0; i < M; i++ ) {
        if ( arcos[i].m == 0 ) {
            if ( menor == -1 )
                menor = i;
            else
                if ( arcos[i].w < arcos[menor].w  )
                    menor = i;
                else
                    if ( arcos[i].w == arcos[menor].w ) 
                        if ( arcos[i].u + arcos[i].w + arcos[i].v < 
                             arcos[menor].u + arcos[menor].w + arcos[menor].v )
                            menor = i;
        }
    }
    return menor;
}

void unirComponentes( int * vertices, int N, int c1, int c2 ) {
    int i;
    for ( i = 0; i < N; i++ )
        if ( vertices[i] == c2 )
            vertices[i] = c1;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int N, M, S, vs, vl, d;
    int **graph;
    Arco *arcos;
    int *vertices;
    
    int i, j, k;
    scanf("%d%d",&N, &M);
    graph = (int **)malloc(N*sizeof(int *));
    for ( i = 0; i < N; i++ )
        graph[i] = (int *)malloc( N*sizeof(int) );    

    for ( i = 0; i < N; i++ )
        for ( j = 0; j < N; j++ )
           graph[i][j] = -1;
    
    for ( i = 0; i < M; i++ ) {
        scanf("%d%d%d", &vs, &vl, &d );
        vs--;vl--;
        if ( vl > vs ) {
            int t = vs; vs = vl; vl = t;
        }
        if ( graph[vs][vl] == -1 || graph[vs][vl] > d )
            graph[vs][vl] = d;
        /*graph[vl][vs] = graph[vs][vl];*/
    }

    M = 0;
    for ( i = 0; i < N; i++ )
        for ( j = 0; j < N; j++ )
           if ( graph[i][j] >= 0 )
               M++;
    
    arcos = (Arco *)malloc( M*sizeof(Arco) );
    for ( k = i = 0; i < N; i++ )
        for ( j = 0; j < N; j++ )
            if ( graph[i][j] >= 0 ) {
                arcos[k].u = i;
                arcos[k].v = j;
                arcos[k].w = graph[i][j];
                arcos[k].m = 0;
                k++;
            }

    for ( i = 0; i < N; i++ )
        free( graph[i] );
    free( graph );
    
    vertices = (int *)malloc( N*sizeof(int) );
    for ( i = 0; i < N; i++ )
        vertices[i] = i;
    
    scanf("%d", &S); //ignored
    S--;

    int menor, u, v;
    while ( (menor = menorArco(arcos,M)) >= 0 ) {
        u = arcos[menor].u;
        v = arcos[menor].v;
        if ( vertices[u] != vertices[v] ) {
            unirComponentes( vertices, N, vertices[u], vertices[v]);
            arcos[menor].m = 1;
        }
        else
            arcos[menor].m = -1;
    }

    long R;
    R = 0;
    for ( i = 0; i < M; i++ )
        if ( arcos[i].m == 1 )
            R = R + arcos[i].w;
    
    printf("%ld",R);

   
    return 0;
}
