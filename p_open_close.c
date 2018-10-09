#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

#define CHILD !forked

#define PARENT forked

int main (int argc, const char * argv[]) {

		char programName[11];
		
		char array[10000];

		int i = 0;

		int pipe_fd[2];

		FILE *fd ;

		pid_t forked ; 

		pipe(pipe_fd);

		char buf;

		forked = fork () ;

		if ( PARENT ) {

				close (pipe_fd[0]);      /* closing read channal */

				printf("Type in the name of the program you would like to open: ");

				scanf("%[^\n]s", programName);

				fd = popen ( programName,"r" ) ;

				while ( ( buf = fgetc( fd ) ) != EOF ) 
			
							array[i++] = buf ;
							
						array[i] = '\0' ;

						if ( ( write (pipe_fd[1], array , strlen(array)) ) == EOF ) {

								printf("internal error\n");
							
								exit ( EXIT_FAILURE );

							}

				close (pipe_fd[1]); 

				pclose(fd);

				wait(NULL);

				exit ( EXIT_SUCCESS ) ;

		}

		if ( CHILD ) {

				close (pipe_fd[1]) ;     /* closing write pipe */

				while ( (read ( pipe_fd[0] ,&buf , 1) ) > 0 ) 

						write (STDOUT_FILENO , &buf , 1 ) ;

				close(pipe_fd[0]);

				return 0; 


		}	

		/*	if ( pclose ( popen(programName ,"w") ) == -1 ) {

			puts(" pclose() failed " );

			}*/

		/*

		 * popen will return file descriptor
		 * where as pclose takes a file descriptor as its argument 
		 *so cool

		 */

		return 0;

}
