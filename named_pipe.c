#include	<stdio.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/stat.h>

int main ( void ) {

		int res = mkfifo ("_fifo" , 0777) ;

		if ( res == 0 ) 
		
				puts("fifo created");

		exit ( EXIT_SUCCESS ) ;

}
