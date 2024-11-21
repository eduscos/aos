q1) -----
-> #include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, char *argv[])
{
struct stat fileStat;
if(argc!=3)
{ printf("Invalid number of arguments ");
return 1;
}
int file1 = open(argv[1], O_RDONLY);
if(file1 < 0)
{
fprintf(stderr, "error opening file1\n");
return 1;
}
int file2 = open(argv[2], O_RDONLY);
if(file2 < 0)
{
fprintf(stderr, "error opening file2\n");
return 1;
}
if(fstat(file1,&fileStat)<0)
return 1;
printf("File1 is:%s and Inode:%ld\n",argv[1],fileStat.st_ino);
if(fstat(file2,&fileStat)<0)
return 1;
printf("File2 is:%s and Inode:%ld\n",argv[2],fileStat.st_ino);
}





q2)-----
->  #include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void signalHandler(int signal) // this is signal handler for
{
 if (signal == SIGALRM)
 {
 printf("Ding!\n");
 wait(NULL);
 }
}
int main(int argc, char *argv[])
{
  signal(SIGALRM, signalHandler);
 if (argc != 2)
 {
 printf("Invalid arguments\n");
 return 0;
 }
 printf("Alarm application starting\n");
 int delay;
 sscanf(argv[1], "%d", &delay);
if (fork() == 0) // start child process
 {
 printf("Waiting for alarm to go off\n");
 sleep(delay);
 kill(getppid(), SIGALRM);
 exit(0);
 }
 wait(NULL);
 printf("done\n");
}
