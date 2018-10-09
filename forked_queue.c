#include	<uma.h>

#include	<signal.h>

#include	<semaphore.h>

#include	<sys/stat.h>

#include	<fcntl.h>

#include    <mqueue.h>

struct mq_attr attr ;

mqd_t md ;

int prio ;

sem_t *sem ;

sem_t *sem2 ;

#define CHILD !forked

#define PARENT forked

void _HAND ( int no ) {

	sem_close(sem);

	sem_close(sem2);

	sem_unlink ("/ffi");

	sem_unlink ("/ffi2");

	puts(R"received SIGINT terminating process"Z);

	mq_unlink("/_mq");

	exit (EXIT_SUCCESS) ;

}

int main ( void ) {

	signal ( SIGINT , _HAND ) ;

	pid_t forked ;

	sem = sem_open ( "/ffi" , O_CREAT | O_RDWR , 0777 , 0 );

	sem2 = sem_open ( "/ffi2" , O_CREAT | O_RDWR , 0777 , 1 );

	char buffer[88];

	if ( ( forked = fork () ) < 0 )  {

		perror("forking");

		exit ( EXIT_FAILURE ) ;
	}

	if ( PARENT ) {

		attr.mq_maxmsg = 10;

		//printf("in while parent %d %d\n", *sem ,*sem2);

		attr.mq_msgsize = 90;

		while (1) {

			sem_wait ( sem2 ) ;

			if ( ( md = mq_open ( "/_mq" , O_CREAT | O_WRONLY , 0777 , &attr )  ) == -1 ) { 

				perror("parent open");

				exit ( EXIT_FAILURE ) ;
			}

			puts (B"enter message"Z) ;

			__fpurge(stdin) ;

			if ( !fgets( buffer , 88 , stdin ) ) {

				perror("fgets");

				exit ( EXIT_FAILURE ) ;
			}

			//	printf("%ld\n",attr . mq_msgsize );

			if ( buffer  [ strlen(buffer) - 1 ] =='\n')

				buffer  [ strlen(buffer) - 1 ] =='\0';

			if ( ( mq_send ( md , buffer , 88 , 1  ) ) == -1 ) {

				perror("sending");

				//								exit ( EXIT_FAILURE ) ;

			}

			sem_post ( sem ) ;
		}
	}

	if ( CHILD ) {

		while ( 1 ) {

		//	printf("in while child %d %d\n", *sem ,*sem2);

			sem_wait ( sem ) ;

			//puts("child aftr sem");

			if ( ( md = mq_open ( "/_mq" , O_RDWR , 0777 , NULL )  ) == -1 ) {

				perror("child open");

				exit ( EXIT_FAILURE ) ;

			}

			//puts("child aftr sem");
			
			if ( ( mq_getattr ( md , &attr ) == -1 ) ) {

				perror ( "get attributes" );

				exit (EXIT_FAILURE) ;

			}

			//	printf("%ld\n",attr . mq_msgsize );
			//	printf("%ld\n",attr . mq_maxmsg );
			//	printf("%d\n",sizeof(buffer) );

			if ( mq_receive ( md , buffer , 90 + 1 , &prio )  == -1) {

				perror("receive");

				exit (EXIT_FAILURE); 

			}	

			printf(R"the message is %s"Z ,buffer);

			mq_unlink("/_mq");

			sem_post (sem2 ) ;

		}

	}

}
