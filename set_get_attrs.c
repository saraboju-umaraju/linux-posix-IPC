#include	<uma.h>
#include	<fcntl.h>
#include	<mqueue.h>

int main ( void ) {

		struct mq_attr *attr = malloc(200) ;

		struct mq_attr new ;

		mqd_t md ;
	
		int temp = 0 ;

		new . mq_maxmsg = 30 ;
		
		new . mq_msgsize = 30 ;

		md = mq_open ( "/_mq" , O_CREAT | O_RDWR , 0777 , &new ) ;

		temp = mq_getattr ( md , attr );

		printf("%d  %d \n",md,temp);

		printf("%ld\n", attr ->  mq_maxmsg);
		
		printf("%ld\n", attr ->  mq_msgsize);

		printf("%ld\n", new . mq_maxmsg);
		
		printf("%ld\n", new . mq_msgsize);


}
