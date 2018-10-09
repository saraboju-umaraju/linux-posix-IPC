#include	<uma.h>
#include	<sys/mman.h>
#include	<fcntl.h>
int main ( void ) {

	int fd = open ("./file.txt" , O_RDWR | O_CREAT ) ;	

	printf("%d %p\n",fd , sbrk(0));

	char *ptr ;

    if ( ( ptr =  mmap ( NULL , ( 1 * 4096 ) , PROT_WRITE | PROT_READ ,MAP_SHARED , fd , 0 ) ) == MAP_FAILED ) {

        perror("mappin");

        exit ( EXIT_FAILURE ) ;

    }

	printf("%p\n",sbrk(0));
	
	printf("%p\n",ptr);

}
