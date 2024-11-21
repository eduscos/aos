q1)
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
if(access(argv[1],F_OK)==0)
printf("File %s exists in current directory \n", argv[1]);
else
printf("File %s doesn't exist in current directory \n", argv[1]);
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
printf("\nPARENT: sending SIGQUIT\n\n");
kill(pid, SIGQUIT);
sleep(3); // pause for 3 seconds
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
