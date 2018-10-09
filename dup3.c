#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#define OUTPATH "kill"
#define MESSAGE "aha i wanted to live in STDOUT"
 
int main() {
    
	int new_out = -1;
 
    new_out = open(OUTPATH, O_WRONLY | O_CREAT | O_TRUNC,
                S_IRWXU | S_IRGRP | S_IROTH);
 
    if (new_out < 0) {
        
		perror("open(2) file: " OUTPATH);
        
		exit(EXIT_FAILURE);
    }
 
    if (close(STDOUT_FILENO) < 0) {
        
		perror("close(2) file: STDOUT_FILENO");
        
		close(new_out);
        
		exit(EXIT_FAILURE);
    }
 
    if ( dup(new_out) != STDOUT_FILENO ) {
        
		perror("dup(2)");
        
		close(new_out); 
        
		exit(EXIT_FAILURE);
    }
 
    close(new_out); 
    
	printf(MESSAGE); 
 
    return EXIT_SUCCESS;
}
