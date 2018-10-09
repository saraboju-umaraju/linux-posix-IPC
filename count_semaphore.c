#include	<pthread.h>

#include	<uma.h>

#include	<stdlib.h>

#include	<semaphore.h>

#include	<fcntl.h>

#include	<signal.h>

sem_t *sem_one ;

void _hand( int u ) {	

	puts("test");

	free ( sem_one ) ;

	sem_close( sem_one );

//	sem_unlink ("/_u");

	exit ( EXIT_SUCCESS ) ;

	}

int *func ( void *p ) {

	int var = *(int*)p ;
		
	while(1) {
	
	sem_wait ( sem_one );

	printf("thread running %d\n" , var);
	
	usleep (1000000);

	printf("thread exiting %d\n",var);

	usleep(1000000);
	
	sem_post ( sem_one );

	usleep(1);

//	exit( EXIT_SUCCESS ) ;

	}

}

int main ( void ) {

		signal ( SIGINT , _hand ) ;
		
		sem_one = malloc ( sizeof ( sem_t ) ) ;

		//sem_one = sem_open ( "/_u" , O_CREAT | O_RDWR , 0777 , 2 ) ;

		sem_init ( sem_one , 0 , 3 ) ;
	
		pthread_t one ;

		pthread_t two ;
		
		pthread_t three ;
		
		pthread_t four ;
		
		pthread_t five ;
		
		pthread_t six ;

		//dont know array yet

		int v_one = 1 ;

		int v_two = 2 ;
		
		int v_three = 3 ;
		
		int v_four = 4 ;
		
		int v_five = 5 ;
		
		int v_six = 6 ;

		//dont know enum yet

		if (  ( pthread_create ( &one , NULL , (void*)&func , &v_one ) ) ) {

				perror("one");

				exit (EXIT_FAILURE);

		}

		if (  pthread_create ( &two , NULL , (void *)func , &v_two ) ) {

		perror("two");

                exit (EXIT_FAILURE);

        }

		
		if (  pthread_create ( &three , NULL , (void*)func , &v_three ) ) {

		perror("three");

                exit (EXIT_FAILURE);

        }

		
		if ( pthread_create ( &four , NULL , (void*)func , &v_four ) ) {

		perror("four");

                exit (EXIT_FAILURE);

        }

		if (  pthread_create ( &five , NULL , (void*)func , &v_five ) ) {

        perror("five");

                exit (EXIT_FAILURE);

        }


        if ( pthread_create ( &six , NULL , (void*)func , &v_six ) ) {

        perror("six");

                exit (EXIT_FAILURE);

        }


		//dont know loop yet
	
		pthread_join( one , NULL );
		
		pthread_join( two , NULL );
		
		pthread_join( three , NULL );
		
		pthread_join( four , NULL );
		
		pthread_join( five , NULL );
		
		pthread_join( six , NULL );

		getchar();

}

