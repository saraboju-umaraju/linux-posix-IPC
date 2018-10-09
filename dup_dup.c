#include	<stdio.h>

#include	<fcntl.h>

int main ( void ) 
{

	int new = open("l", O_CREAT | O_RDWR);;

	perror("");

	close(1);

	perror("");

	dup(new);

	perror("");

	write(1, "uma" ,4 ) ;

	perror("");
}
