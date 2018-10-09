#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

        char buff1[120];


mqd_t mq_fd1;
int main ( void )
{


        int f_value;


        char buff2[5];

        unsigned prio = 1 ;
        mq_unlink("/mq2");

        if( ( mq_fd1 = mq_open("/mq2",O_CREAT| O_RDWR  ,0777, NULL ) ) == -1 ){

                printf ("mesage queue creation failed..!!!\n");

                exit(EXIT_FAILURE);

        }

        f_value = fork();

        if(f_value > 0){

                bzero(buff1,120);
                printf ("enter data:");

                fgets(buff1, 5, stdin);

                if( (mq_send(mq_fd1, buff1 , 8192, 1 ) ) == -1 ){

                        perror("mq_send");

                        printf("%d\n", errno);

                        exit(EXIT_FAILURE);

                }

                wait(NULL);

                }else if( f_value == 0){

                        if( (mq_receive(mq_fd1, buff2, 8192, &prio) ) == -1 ){

                        perror("mq_receive");

                        exit(EXIT_FAILURE);


                        }

                printf ("data recieved:%s  prio = %d\n",buff2, prio);


        }else{

                        printf ("fork failed..!!!\n");

                        exit(EXIT_FAILURE);

                }

                mq_close(mq_fd1);

                return 0;
}
