#include    <pthread.h>

#include    <uma.h>

#include    <_val.h>

#include    <sys/mman.h>

#include    <semaphore.h>

#include    <fcntl.h>

#include    <signal.h>

#include    <stdlib.h>

#define _PAGE_SIZE 4096

static int var = 0;

int fd ;

sem_t *_sem ;

int *ptr = NULL ;

void *thread_func ( ) {

		if ( ( fd = shm_open ( "/_name" , O_CREAT | O_RDWR | O_TRUNC , 0777 ) ) == -1 ) {

				perror("opening shared memory object");

				exit ( EXIT_FAILURE ) ;

		}

		if ( ( ftruncate ( fd , (off_t)( 3 * _PAGE_SIZE ) ) ) == -1 ) {

				perror("truncating shared memory object");

				exit ( EXIT_FAILURE ) ;

		}

		if ( ( ptr =  mmap ( NULL , ( 3 * _PAGE_SIZE ) , PROT_WRITE | PROT_READ ,MAP_SHARED , fd , 0 ) ) == MAP_FAILED ) {

				perror("mappin");

				exit ( EXIT_FAILURE ) ;

		}


		while(1) {

				while ( var != 3 ) ;

				sem_wait ( _sem ) ;

				while ( var ) {

						printf("the node i consumed is %d \n" , *( ptr + --var) );

						printf("var is %d \n" , (var) );


				}

						sem_post ( _sem ) ;
		}

}

void _hand ( ) {

		sem_close ( _sem ) ;

		sem_unlink ("/_sem");

		puts("handled");

		exit ( EXIT_SUCCESS );

} 

int main ( void ) {

		int temp = 0 ;	

		pid_t fo ;

		signal ( SIGINT , _hand ) ;

		if ( ! (_sem = malloc ( sizeof ( sem_t ) ) ) ) {

				perror("memory allocation");

				exit ( EXIT_FAILURE ) ;

		}

		_sem = sem_open ( "/_sem" , O_CREAT , 0777 , 1 ) ; 

		pthread_t thread_ID ;

		if ( pthread_create ( &thread_ID , NULL , thread_func , NULL ) ) {

				perror("truncating shared memory object");

				exit ( EXIT_FAILURE ) ;

		}

		fo = fork() ;

		if ( fo ) {	

				if ( ( fd = shm_open ( "/_name" , O_CREAT | O_RDWR | O_TRUNC , 0777 ) ) == -1 ) {

						perror("opening shared memory object");

						exit ( EXIT_FAILURE ) ;

				}

				if ( ( ftruncate ( fd , (off_t)( 3 * _PAGE_SIZE ) ) ) == -1 ) {

						perror("truncating shared memory object");

						exit ( EXIT_FAILURE ) ;

				}

				if ( ( ptr =  mmap ( NULL , ( 3 * _PAGE_SIZE ) , PROT_WRITE | PROT_READ ,MAP_SHARED , fd , 0 ) ) == MAP_FAILED ) {

						perror("mappin");

						exit ( EXIT_FAILURE ) ;

				}

				* ( ptr + var ) = var ;

				var++; 

				while ( 1 ) {

						sem_wait ( _sem ) ;

						puts("parent");

						temp = _val(NULL);

						* ( ptr + var++ ) = temp ;

						sem_post ( _sem ) ;

						usleep(100);

				}


		} // end of parent

		if ( !fo ) {

				if ( ( fd = shm_open ( "/_name" , O_CREAT | O_RDWR | O_TRUNC , 0777 ) ) == -1 ) {

						perror("opening shared memory object");

						exit ( EXIT_FAILURE ) ;

				}

				if ( ( ftruncate ( fd , (off_t)( 3 * _PAGE_SIZE ) ) ) == -1 ) {

						perror("truncating shared memory object");

						exit ( EXIT_FAILURE ) ;

				}

				if ( ( ptr =  mmap ( NULL , ( 3 * _PAGE_SIZE ) , PROT_WRITE | PROT_READ ,MAP_SHARED , fd , 0 ) ) == MAP_FAILED ) {

						perror("mappin");

						exit ( EXIT_FAILURE ) ;

				}

				while ( 1 ) {

						sem_wait ( _sem ) ;

						puts("child");

						temp = _val(NULL);

						* ( ptr + var++ ) = temp ;

						sem_post ( _sem ) ;

						usleep(100);
				}


		} // end of


}
