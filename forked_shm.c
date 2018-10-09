/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */

/*propreitary of umaraZ Inc */

#include	<uma.h>

#include	<stdlib.h>

#include	<sys/mman.h>

#include	<signal.h>

#include	<semaphore.h>

#include	<sys/stat.h>

#include	<fcntl.h>

#include    <mqueue.h>

#include 	<string.h>

sem_t *sem ;

sem_t *sem2 ;

#define CHILD !forked

#define PARENT forked

#define ONE_PAGE 4096

void _HAND ( int no ) {

	sem_close(sem);

	sem_close(sem2);

	sem_unlink ("/one");

	sem_unlink ("/two");

	puts("received SIGINT terminating process");

	exit (EXIT_SUCCESS) ;

}

int main ( void ) {

	signal ( SIGINT , _HAND ) ;

	pid_t forked ;

	int fd ;

	char *pointer = NULL ;

	off_t length = ONE_PAGE + 1 ;


	sem = sem_open ( "/one" , O_CREAT | O_RDWR , 0777 , 0 );

	perror("sem open");

	sem2 = sem_open ( "/two" , O_CREAT | O_RDWR , 0777 , 1 );

	printf("%d\n" , *sem2 );

	if ( ( forked = fork () ) < 0 )  {

		perror("forking");

		exit ( EXIT_FAILURE ) ;

	}

	if ( PARENT ) {		

		while ( 1 ) {

			sem_wait( sem2 ) ;  /* make 0 if it is 1 */

			if ( ( fd = shm_open ( "/_sh" , O_CREAT | O_RDWR | O_TRUNC , 0777 )  ) == -1 ) {

				perror ("opening a shared memory object") ;

				exit ( EXIT_FAILURE ) ;

			}

			if ( ftruncate ( fd , (off_t)length ) == -1 ) {

				perror ("truncating the shared memory object");

				exit ( EXIT_SUCCESS ) ;

			}

			if ( ( pointer = ( mmap ( NULL , length , PROT_WRITE , MAP_SHARED , fd , 0 ) ) ) == ( void * ) -1 ) {

				perror("mapping file");

				exit ( EXIT_FAILURE ) ;

			}

			puts ( "enter any useless message" );

			if ( ! ( fgets ( pointer , ONE_PAGE + 1 , stdin ) ) ) {

				perror("reading string");

				exit ( EXIT_FAILURE ) ;

			}

			if ( pointer[ strlen ( pointer ) - 1 ] == '\n' )

				pointer[ strlen ( pointer ) - 1 ] = '\0' ;

			if ( ( munmap ( pointer , ONE_PAGE ) ) == -1 ) {

				perror ( "unmapping" );

				exit ( EXIT_FAILURE ) ;

			}
			close(fd);

			sem_post( sem ); /* make 1 from zero */
		}

	}

	if ( CHILD ) {

		while ( 1 ) {

			sem_wait( sem ) ;

			if ( ( fd = shm_open ( "/_sh" ,  O_RDWR  , 0777 )  ) == -1 ) {

				perror ("opening a shared memory object") ;

				exit ( EXIT_FAILURE ) ;

			}

			if ( ( pointer = ( mmap ( NULL , length , PROT_WRITE | PROT_READ , MAP_SHARED , fd , 0 ) ) ) == ( void * ) -1 ) {

				perror("mapping file");

				exit ( EXIT_FAILURE ) ;

			}

			printf("the message is %s\n",pointer);

			if ( (munmap ( pointer , ONE_PAGE ) ) == -1 ) {

				perror("unmapping");

				exit ( EXIT_FAILURE ) ;

			}

			if ( shm_unlink ("/_sh") == -1 ) {

				perror("unlinking shared memory object");

				exit ( EXIT_FAILURE ) ;

			}


			close(fd);
			sem_post( sem2 );

		}

	}

}
