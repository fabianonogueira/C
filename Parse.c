/*

Compilar: gcc Parse.c -o Parse
Executar: ./Parse

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	int N;
	int ID[20][100];
} CASO;

typedef struct {
	int T;
	CASO C[10];
} TESTE;

TESTE readFile( char *nome);
int extract_TESTE( char *line , int *valor);


int extract_TESTE( char *line, int *valor)
{
	char *p;
	char *n = line;
	char aux[10];
	int size;
	int need_break = 0;
	int count = 0;
	while ( *n ) {
		p = strstr(n, " ");
		if( p !=NULL ) {
			size = (p - n);
			memcpy(aux, n, size);
			aux[size]='\0';
			n=p+1;			
		}
		else {
			sprintf(aux, "%s", n);
			size = strlen(aux);	
			need_break = 1;
		}		
		valor[count] = atoi(aux);
		count++;
		if( need_break ){
			break;
		}
	}
	return count;
}



TESTE readFile( char *nome)
{
	TESTE x;
	FILE *arq;
	char line[1000];
	int valor[100];
	int count;
	int passo;
	int C;
	int N;
	arq = fopen( nome, "r" );
	if( arq == NULL	){
		return x;
	}
	passo = 1;
	C=0;
	N=0;
	printf("\n\n\n");
	while( fgets( line, 1000, arq )!=NULL ) {
		count = extract_TESTE( line, valor );
		N--;
		for( int i=0; i<count; i++ ){
			switch( passo ) {
				case 1: x.T = valor[i];
						passo = 2;
						break;
				case 2: x.C[C].N = N = valor[i];
						passo = 3;					
						break;
				case 3: x.C[C].ID[x.C[C].N-N-1][i] = valor[i];							
						if( N == 0 ){
							passo = 2;
							C++;
						}																				
						break;					
			}
		}
	}
	fclose( arq );
	return x;
}




int main(int argc, char const *argv[])
{
	int N;
	TESTE x;

	x = readFile("Parse.txt");
	printf("\n\n\n");
	printf("x.T = %d\n",x.T);
	for( int i=0; i<x.T; i++ ){
		printf("x.C[%d].N = %d\n",i,x.C[i].N);
		for( int j=0; j<x.C[i].N; j++ ){
			for( int z=0; x.C[i].ID[j][z]!=0; z++ ){
				printf("x.C[%d].ID[%d][%d] = %d\n",i,j,z, x.C[i].ID[j][z]);
			}
		}
	}


	
	return 0;
}