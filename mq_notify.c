#include	<mqueue.h>

#include	<signal.h>

#include	<uma.h>

#include	<fcntl.h>

#include <stdlib.h>

mqd_t md ;

void *tfunc() {
	puts("hello");
	exit (1);
}

struct mq_attr attr ;

int main ( void ) {

		char buffer [20] = "" ;

		unsigned int prio = 1 ;

		struct sigevent inst ;

		signal ( SIGUSR1 , tfunc ) ;


		int var = 10 ;

		if (( md = mq_open ( "/_mq" , O_RDONLY  , 0777 , NULL ) ) == -1 ) {

				perror("ERROR");

				exit ( EXIT_FAILURE ) ;

		}

		printf("%d\n",md);
		
		inst . sigev_notify = SIGUSR1 ;

		//inst.sigev_notify_function = tfunc;
           inst.sigev_notify_attributes = NULL;
           inst.sigev_value.sival_ptr = &md;  
 if (mq_notify(md, &inst) == -1) printf("failed");

		if( mq_getattr ( md , &attr ) ) {

				perror("ERROR");

				exit ( EXIT_FAILURE ) ;

		}

		printf("%d\n",attr.mq_msgsize);

		while ( var ) {
	
		if (  (mq_receive ( md , buffer, attr . mq_msgsize + 1 , &prio ) ) == -1 ) {

				perror("ERROR");

				exit (EXIT_FAILURE) ;

		}
		
		printf ("the message is %s \n",buffer);

		var--;

		}

		if ( ( mq_unlink( "/_mq" ) ) == -1 ) {

				perror ("ERROR") ;

				exit ( EXIT_FAILURE ); 

		}


}


