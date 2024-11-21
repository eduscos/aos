q1)
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



q2)
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<fcntl.h>
int main(int argc, char const *argv[])
{
if(argc != 2){
fprintf(stderr, "usage : %s <filepath>\n", argv[0]);
return 1;
}
int file = open(argv[1], O_RDONLY);
if(file < 0){
fprintf(stderr, "error opening file\n");
return 1;
}
struct stat st;
if(fstat(file, &st) < 0)
{
fprintf(stderr, "error reading file info\n");
return 1;
}
printf("File Name is %s : \n", argv[1]);
printf("File Type: ");
 switch (st.st_mode & S_IFMT)
 {
 case S_IFBLK: printf("this block device\n"); break;
 case S_IFCHR: printf("this character device\n"); break;
 case S_IFDIR: printf("this directory\n"); break;
 case S_IFIFO: printf("this FIFO/pipe\n"); break;
 case S_IFLNK: printf("this symlink\n"); break;
 case S_IFREG: printf("this is regular file\n"); break;
 case S_IFSOCK: printf("this socket\n"); break;
 default: printf("unknown?\n"); break;
 }
return 0;
}
