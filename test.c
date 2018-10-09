#include	<stdio.h>

int main ( void ) {

	char c ;

	FILE *fd = popen ( "ps  " , "r" ) ;

	while( ( c = fgetc(fd) ) != EOF )

		printf("%c",c);

}
