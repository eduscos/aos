q1)
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void main()
{
int fd;
fd = open("output.txt",O_CREAT| O_WRONLY, 0777);
close(STDOUT_FILENO);
dup(fd);
printf("this is some text to be printed on the screen\n");
printf("but it will be written to the file output.txt\n");
}



q2)
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<errno.h>
void main()
{
int filedes[2];
if (pipe(filedes) == -1)
{
perror("pipe");
exit(1);
}
if(fork() == 0)
{
while ((dup2(filedes[1], STDOUT_FILENO) == -1)) {}
char *args[] = {"ls","-l", NULL};
int ret = execvp("ls",args);
if(ret <0)
{
printf("Program can't be executed\n");
}
exit(0);
}
close(filedes[1]);
if(fork() == 0)
{
while((dup2(filedes[0], STDIN_FILENO) == -1)){}
char *args[] = {"wc","-l", NULL};
int ret = execvp("wc",args);
if(ret <0)
{
printf("Program can't be executed\n");
}
exit(0);
}
char output[100];
read(filedes[0], output, 100);
printf("%s", output);
close(filedes[0]);
exit(0);
}
