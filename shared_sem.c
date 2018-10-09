#include	<uma.h>

#include	<semaphore.h>

sem_t sem ;

sem_t sem2 ;

int main ( void ) {

	sem_init ( &sem , 1 , 0 ) ;
	
	sem_init ( &sem2 , 1 , 1 ) ;

	pid_t f = fork();

	if ( f ) {

		sem_wait( &sem2 ) ;

		puts("iam parent");
		
		sem_post( &sem ) ;

		wait(NULL);

		}

	if ( !f ) {
	
		sleep(2) ;

		printf("%d\n",sem);

		sem_wait( &sem ) ;

        puts("iam child");

		sleep( 1 );

        sem_post( &sem2 ) ;

		return 1;

	}

}



	
