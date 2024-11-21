q1)
#include<stdio.h>
#include<dirent.h>
int main()
{
DIR *d;
int cnt=0;
struct dirent *dir; // pointer for directory entry
d=opendir(".");
if(d==NULL)
{
printf("Could not open the current directory");
return(0);
}
while((dir=readdir(d))!=NULL)
{
printf("%s\n",dir->d_name);
cnt++;
}
printf("\nTotal no. of files in the current directory=%d\n",cnt);
closedir(d);
return 0;
}


q2)
#include<stdio.h>
#include<unistd.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
 int pipefds[2];
 int returnstatus;
 int pid;
 char writemessages[3][50]={"Hello world","Hello SPPU","Linux is Funny"};
 char readmessage[50];
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
 printf("Child Process write Messaages\n");
 printf("%s\n", writemessages[0]);
 write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
 printf("%s\n", writemessages[1]);
 write(pipefds[1], writemessages[1], sizeof(writemessages[1]));
 printf("%s\n", writemessages[2]);
 write(pipefds[1], writemessages[2], sizeof(writemessages[2]));
}

 else
 { //Parent process
 sleep(5);
 printf("Parent Process Display Messaages\n");
 read(pipefds[0], readmessage, sizeof(readmessage));
 printf("%s\n", readmessage);
 read(pipefds[0], readmessage, sizeof(readmessage));
 printf("%s\n", readmessage);
 read(pipefds[0], readmessage, sizeof(readmessage));
 printf("%s\n", readmessage);
 }
 return 0;
}
