#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char * phrase = "Stuff this in your pipe and smoke it";

int main () {
  int fd1; 
  fd1 = open ( "mypipe", O_WRONLY|O_CREAT,0777 ); 
  write (fd1, phrase, strlen ( phrase)+1 ); 
  close (fd1);
}

