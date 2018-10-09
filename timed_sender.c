#include	<uma.h>

#include	<fcntl.h>

#include	<mqueue.h>

mqd_t md ;

struct mq_attr new_attr ;

struct mq_attr old_attr ;

int main ( void ) {

		new_attr . mq_maxmsg = 10 ;

		new_attr . mq_msgsize = 100 ;

		unsigned int prio = 1 ;

		int var = 10 ;

		char buffer[100];

		if ( ( md = mq_open ( "/_mq" , O_CREAT | O_WRONLY  , 0777 , &new_attr ) ) == -1 ) {

				perror ("open") ;

				exit ( EXIT_FAILURE ) ;

		}

		while ( var )  {

		puts("enter a string");

		if ( ! (fgets(buffer , 10 , stdin) ) ) {

			puts("fgets");

				exit( EXIT_FAILURE );
		
		}

		if ( mq_send ( md , buffer , 6 , prio ) == -1 ) {

				puts ("send");

				exit ( EXIT_FAILURE ) ;

		}

	}

}  
