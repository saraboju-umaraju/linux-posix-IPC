#include <unistd.h>/*Included for dup(2) and write(2)*/

#include <stdlib.h> /*Included for exit(3)*/

#define MESSAGE "Hey! Who redirected me?"

int main() {

		int newfd = dup2(STDOUT_FILENO , 5); /*Call dup for an aliased fd*/

		char buff[] = MESSAGE;

		printf("new is %d\n",newfd);

		if (newfd < 0) { /*Negative file descriptors are errors*/

				exit(EXIT_FAILURE);

		}

		else if (write(newfd, buff, sizeof(buff)) < 0) { /*buff is const here so newfd is variable*/

				exit(EXIT_FAILURE);

		}

		write(1, buff, sizeof(buff)) ;

	
		return EXIT_SUCCESS;
}
