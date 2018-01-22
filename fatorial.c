#include "stdio.h"


int fatorial ( int n)
{
	if( n < 1 )
		return 1;
	else
		return 	( n * fatorial(n-1) );
}


void fibonacci( void )
{
	int n  = 0;
	int n1 = 1;
	int n2 = 0;

	for(int i = 0; i<10; i++ )
	{
		printf("%d, ", n);
		n  = n1 + n2;
		n1 = n2;
		n2 = n;
	}
}

void main (void)
{
	for(int i=1; i<6; i++)
	{
		printf("Fatorial %d = %d\n\n", i, fatorial(i));
	}

	printf("\n\n\nFibonacci\n");
	fibonacci();
}
