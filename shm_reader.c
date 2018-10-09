#include	<uma.h>

#include	<sys/types.h>

#include	<sys/stat.h>

#include	<fcntl.h>

#include	<sys/mman.h>

#define ONE_PAGE 4096

int main ( void ) {

		int fd ; 

		char buffer[ ONE_PAGE + 1] ;

		char *pointer = NULL ;

		off_t length = ONE_PAGE + 1 ;

		if ( ( fd = shm_open ( "/_sh" ,  O_RDWR  , 0777 )  ) == -1 ) {

				perror ("opening a shared memory object") ;

				exit ( EXIT_FAILURE ) ;
		
		}

		printf("descriptor opened is %d\n" , fd);
		
		if ( ( pointer = ( mmap ( NULL , length , PROT_WRITE | PROT_READ , MAP_SHARED , fd , 0 ) ) ) == ( void * ) -1 ) {

			perror("mapping file");

			exit ( EXIT_FAILURE ) ;

		}

		printf("%s\n",pointer);

		if ( (munmap ( pointer , ONE_PAGE ) ) == -1 ) {

			perror("unmapping");

			exit ( EXIT_FAILURE ) ;

		}
	
		 if ( shm_unlink ("/_sh") == -1 ) {

            perror("unlinking shared memory object");

            exit ( EXIT_FAILURE ) ;

        }


}
