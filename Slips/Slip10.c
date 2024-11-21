q1)
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
int pfds[2];
char buf[80];
if(pipe(pfds)==-1)
{
perror("pipe failed");
exit(1);
}
if(!fork())
{
close(1);
dup(pfds[1]);
system ("ls -l");
}
else
{
printf("parent reading from pipe \n");
while(read(pfds[0],buf,80))
printf("%s \n" ,buf);
}
}



q2)
#include<stdio.h>
#include<unistd.h>
int main() {
 int pipefds[2];
 int returnstatus;
 int pid;
 char writemessages[1][20]={"Hello"};
 char readmessage[20];
 returnstatus = pipe(pipefds);
 if (returnstatus == -1)
{
 printf("Unable to create pipe\n");
 return 1;
 }
 pid = fork();
 // Child process
 if (pid == 0)
 {
 read(pipefds[0], readmessage, sizeof(readmessage));
 printf("Child Process - Reading from pipe â€“ Message is %s\n", readmessage);
 }
 else
 { //Parent process
 printf("Parent Process - Writing to pipe - Message is %s\n", writemessages[0]);
 write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
 }
 return 0;
}
