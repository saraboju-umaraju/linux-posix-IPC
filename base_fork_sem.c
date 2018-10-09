#include	<semaphore.h>

#include	<fcntl.h>

#include	<stdio.h>

#include    <uma.h>

#include    <stdlib.h>

#include    <sys/mman.h>

#include    <signal.h>

#include    <semaphore.h>

#include    <sys/stat.h>

#include    <fcntl.h>

#include    <mqueue.h>

sem_t *sem ;

sem_t *sem2 ;

int main ( void ) 
{
	
	int fd[2] ;

	malloc(-1);
	
	sem = sem_open( "/semm1", O_CREAT | O_RDWR ,0777, 1 );

	printf ("%d\n" , *sem) ;

	sem2 = sem_open( "/semm3", O_CREAT | O_RDWR ,0777, 0 );

	pid_t id ;

	char buf[20];

	if ( pipe ( fd )  ) 

		perror("pipe");

	id = fork () ;

	if ( id > 0 ) {

			sem_wait ( sem ) ; // makes 0 if 1

			write ( fd[1] , "killer" , 8 ) ;

			perror("write parent"); 


			sem_post ( sem2 ) ; //makes 1 if 0 

			sem_wait ( sem ) ;

//			read ( fd[0] , buf , 8 ) ;

//			perror("read parent");

//			puts( buf ); 

			}

	if ( !id ) {

			sem_wait ( sem2 ) ;

            read ( fd[0] , buf , 8 ) ;

            perror("read child");

			puts( buf ); 
		   
//			write ( fd[1] , "killerr" , 8 ) ;

  //          perror("write child");

	//		sem_post ( sem2 ) ;

            }
	//some dumbfuck wrote this without proper validation


if ( sem_unlink ( "/semm1" ) == -1 )
perror("unlink");
if ( sem_unlink ( "/semm3" ) == -1 )
perror("unlink");

}
