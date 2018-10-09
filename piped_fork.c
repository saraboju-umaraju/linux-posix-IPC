#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include	<uma.h>

int main( int c , char * v[] )  {


		pid_t proc_id ;

		int pipe_fd [2] ;

		char buf;

		if ( c != 2 ) {

			fprintf(stderr , "usage %s <string>\n" , v[0]);

			exit (EXIT_FAILURE ) ;

		}
			if ( pipe (pipe_fd ) == -1 ) {

					fprintf(stderr , "internal error\n");

					exit(EXIT_FAILURE);

			}

		if ( ( proc_id = fork ( ) ) < 0)  {

				fprintf(stderr , "internal error\n");

				exit(EXIT_FAILURE) ;

			}


			if ( ! proc_id ) {

					close ( pipe_fd [0] ) ;     /* read channel not needed here */

					write ( pipe_fd [1] , v[1] , strlen( v[1] ) ) ;

					close ( pipe_fd[1] ) ;
			
					//wait (  NULL ) ;    /* parent is on hold */

					exit(EXIT_SUCCESS);
					

			}

			if ( proc_id ) {
					
					wait(NULL);

					close ( pipe_fd [1] ) ;   /* closing write channal */

					puts("receUived message is:");

					while ( read ( pipe_fd [0] , &buf , 1 ) > 0 )

								write ( STDOUT_FILENO , &buf , 1 ) ;
								
					write ( STDOUT_FILENO , "\n" , 1 ) ;

					close ( pipe_fd[0] ) ;

					exit( EXIT_SUCCESS );


			}


			return 0 ;

	}
