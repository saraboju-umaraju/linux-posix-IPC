#include	<stdio.h>

int main ( void ) {

		FILE *fd = popen ("man kill" , "r");
	
		FILE *fp = fopen ("kill.txt","w");

		char buffer[10000] ;

		fread ( buffer , sizeof(char) , 100000 , fd ) ;
		
		fwrite ( buffer , sizeof(char) , strlen(buffer) , fp ) ;

		printf("%s\n",buffer);

		return 0;

} 
