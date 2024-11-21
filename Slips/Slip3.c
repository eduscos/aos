q1)
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<fcntl.h>
int main(int argc, char const *argv[])
{
if(argc != 2)
{
fprintf(stderr, "usage : %s <filepath>\n", argv[0]);
return 1;
}
int file = open(argv[1], O_RDONLY);
if(file < 0)
{
fprintf(stderr, "error opening file\n");
return 1;
}
struct stat st;
if(fstat(file, &st) < 0)
{
fprintf(stderr, "error reading file info\n");
return 1;
}
printf("File Name is %s and ", argv[1]);
 if( S_ISREG(st.st_mode) )
 printf("This is Regular file\n");

 if( S_ISDIR(st.st_mode) )
 printf("This is Directory file\n");

 if( S_ISCHR(st.st_mode) )
 printf("This is Chracter Special file\n");

 if( S_ISBLK(st.st_mode) )
 printf("This is Block Special file\n");

 if( S_ISFIFO(st.st_mode) )
 printf("This is Pipe or FIFO file\n");

 if( S_ISLNK(st.st_mode) )
 printf("This is Symbolic file\n");

 if( S_ISSOCK(st.st_mode) )
 printf("This is Socket file\n");

return 0;
}



q2)
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
// function declaration of sighup, sigint and sigquit functions
void sighup();
void sigint();
void sigquit();
// main function or driver code
void main()
{
int pid;
// pid variable, which will be used later to identify the process, whether it is child process or
parent process
// to get the child process
if ((pid = fork()) < 0)
{
perror("fork");
exit(1);
}
if (pid == 0)
{ /* child process, since pid equals to zero for child process */
signal(SIGHUP, sighup);
signal(SIGINT, sigint);
signal(SIGQUIT, sigquit);
for (;;); /* infinite loop i.e. loop for ever */
}
else /* parent process*/
{ // pid hold the process id of child process
printf("\nPARENT: sending SIGHUP\n\n");
kill(pid, SIGHUP);
sleep(3); // pause for 3 seconds
printf("\nPARENT: sending SIGINT\n\n");
kill(pid, SIGINT);
sleep(3); // pause for 3 seconds
printf("\nPARENT: Waiting for 5 Second then kill child\n\n");
 printf("\nPARENT: sending SIGQUIT\n\n");
kill(pid, SIGQUIT);
sleep(5); // pause for 5 seconds
}
}
// function definition of sighup()
void sighup()
{
signal(SIGHUP, sighup); /* reset signal */
printf("CHILD: I have received a SIGHUP\n");
}
// function definition of sigint()
void sigint()
{
signal(SIGINT, sigint); /* reset signal */
printf("CHILD: I have received a SIGINT\n");
}
// function definition of sigquit()
void sigquit()
{
printf("My Papa has Killed me!!!\n");
exit(0);
}
