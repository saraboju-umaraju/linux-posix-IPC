#include	<uma.h>

#include	<stdlib.h>

#include	<sys/types.h>

#include	<sys/stat.h>

#include	<fcntl.h>

#include	<sys/mman.h>

#define ONE_PAGE 4096

int main ( void ) {

		int fd ; 

		char *pointer = NULL ;

		off_t length = ONE_PAGE + 1 ;

		if ( ( fd = shm_open ( "/_sh" , O_CREAT | O_RDWR | O_TRUNC , 0777 )  ) == -1 ) {

				perror ("opening a shared memory object") ;

				exit ( EXIT_FAILURE ) ;

		}

		printf("descriptor opened is %d\n" , fd);

		if ( ftruncate ( fd , (off_t)length ) == -1 ) {

				perror ("truncating the shared memory object");

				exit ( EXIT_SUCCESS ) ;

		}

		puts ( "enter any useless message" );


		if ( ( pointer = ( mmap ( NULL , length , PROT_WRITE , MAP_SHARED , fd , 0 ) ) ) == ( void * ) -1 ) {

				perror("mapping file");

				exit ( EXIT_FAILURE ) ;

		}

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

}
