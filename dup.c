#include	<uma.h>

int main( void ) {


		FILE* fd = fopen("somefile.txt","r");
		
		FILE* fs = fopen("someotherfile.txt","w");
		
//		dup2 ( fd , fs ) ;

		while ( ! feof(fd) ) {
			
			fputc(fgetc(fd) , fs);

		}

}
