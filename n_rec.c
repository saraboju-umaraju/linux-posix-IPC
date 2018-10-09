#include	<uma.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<mqueue.h>
#include	<signal.h>
void _hand ( int ) ;

char buffer[30];

mqd_t md ;

int main ( void ) {

		struct sigevent inst ;

		inst . sigev_notify =  SIGEV_SIGNAL ;

		inst . sigev_signo = SIGINT ;	

		signal ( SIGINT , _hand ) ;

		if ( ( md = mq_open ( "/_mq2" ,  O_RDONLY , 0777 , NULL ) ) == -1 ) {

				perror("open");

				exit ( EXIT_FAILURE ) ;

		} 

		mq_notify ( md , &inst );

		pause  () ;

		return 100 ;

}



void _hand ( int signo ) {


		int one = 1 ;
		
		if ( ( mq_receive ( md , buffer , 8192 , &one ) ) == -1 ) {

				perror("receiving");

				exit ( EXIT_FAILURE ) ;

		}
		puts(buffer) ;
}
