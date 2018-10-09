#include	<uma.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<mqueue.h>
#include	<signal.h>

int main ( void ) {

		char buffer[30];
	
		mqd_t md ;

		if ( ( md = mq_open ( "/_mq2" , O_CREAT | O_RDWR , 0777 , NULL ) ) == -1 ) {

				perror("open");

				exit ( EXIT_FAILURE ) ;

		}

		while ( 1 ) { 

				puts("enter message");

				if ( ! ( fgets ( buffer , 8 , stdin ) ) ) {

						perror("fgets");

						exit ( EXIT_FAILURE );

				}

				if ( ( mq_send ( md , buffer , 8 , 1 ) ) == -1 ) {

						perror("sending");

						exit ( EXIT_FAILURE ) ;

				}

		}
}
