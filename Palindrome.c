/*

Compilar: gcc Palindrome.c -o Palindrome
Executar: ./Palindrome

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	//char s[1000+1] = "kpsdjsdkfjjfkdsgaskljsaaa";
	char s[1000+1] = "kpsdjsdkfjfkdsgaskljsaaa";
	//char s[1000+1] = "baabad";
	char p[1000+1];
	char a[1000+1];
	memset( p, 0, 1000 );
	printf("\n\nInput: %s",s);
	for( int i=0; i<strlen(s); i++ ) {
		for( int j=0; i-j>-1 && i+j<strlen(s) ; j++) {
			if( s[i-j] == s[i+j] || s[i-j] == s[i+1+j]) {
				memset( a, 0, 1000 );
				memcpy( a, &s[i-j], 1 + 2*j + (s[i-j]==s[i+1+j]?1:0) );
			}
			else {
				if( strlen(a) > strlen(p) ){
					sprintf( p, "%s", a);
				}
				break;
			}
		}
	}
	printf("\nOutput: %s\n\n",p);
	return 0;
}