q1)
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
char d[50];
if(argc==2)
{
bzero(d,sizeof(d));
strcat(d,"ls ");
strcat(d,"> ");
strcat(d,argv[1]);
system(d);
}
else
printf("\nInvalid No. of inputs");
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
