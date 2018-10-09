#include	<uma.h>

#include	<fcntl.h>

#include	<mqueue.h>

mqd_t md ;

struct mq_attr new_attr ;

struct mq_attr old_attr ;

int main ( void ) {

		new_attr . mq_maxmsg = 10 ;

		new_attr . mq_msgsize = 4 ;
 
		md = mq_open ( "/_mq" , O_CREAT  , 0777 , &new_attr ) ;

		mq_getattr( md , &old_attr ) ;

		printf ( "%ld\n" , old_attr . mq_maxmsg ) ;
		
		printf ( "%ld\n" , old_attr . mq_msgsize ) ;
		
		printf ( "%ld\n" , new_attr . mq_maxmsg ) ;
		
		printf ( "%ld\n" , new_attr . mq_msgsize ) ;

		perror("open");

		printf("%d\n" , md);

		mq_close(md);

		perror("close");

		mq_unlink ("/_mq");

		perror("unlink");

}  
