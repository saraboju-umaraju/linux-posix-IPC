#include <unistd.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

int main()

{

		FILE *write_fp;

		char buffer[BUFSIZ + 1];

		sprintf(buffer, "Once upon a time, there was...\n");

		write_fp = popen("ls", "w");

		if (write_fp != NULL) {

				fread(buffer, sizeof(char), strlen(buffer), write_fp);   // from buffer to  write_fp 

				pclose(write_fp);

				exit(EXIT_SUCCESS);

		}
	
		puts(buffer) ;

		exit(EXIT_FAILURE);

}
