#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<fcntl.h>
#include	<sys/stat.h>


int main ( void ) {

	//int fd = open ( "/tmp/_fifo" , O_RDONLY ) ;
	
	//int fp = open ( "/tmp/_fifo" , O_WRONLY ) ;
	
	//int fp = open ( "/tmp/_fifo" , O_WRONLY | O_NONBLOCK ) ;
	
	int fp = open ( "/tmp/_fifo" , O_RDONLY | O_NONBLOCK ) ;

	//printf("%d\n" , fd);
	
	char buf [20] = "";

	read (fp , buf , 10  ) ; 
	
//	write (fp , buf , 10  ) ; 

	printf("%s\n",buf);

//	close(fp);

}	
