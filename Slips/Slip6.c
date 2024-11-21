q1)
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
char in[100],st[100],*ch,*ch1,c,buff[512];
DIR *dp;
int i;
struct dirent *ep;
struct stat sb;
char mon[100];
dp=opendir("./");
if (dp != NULL)
{
while(ep =readdir(dp))
{
if(stat(ep->d_name,&sb) == -1)
{
perror("stat");
exit(EXIT_SUCCESS);
}
strcpy(mon,ctime(&sb.st_ctime));
ch=strtok(mon," ");
ch=strtok(NULL,",");
ch1=strtok(ch," ");
if((strcmp(ch1,argv[1]))==0)
{
printf("%s\t\t%s",ep->d_name,ctime(&sb.st_ctime));
}
}
(void)closedir(dp);
}
return 0;
}



q2)
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include<sys/times.h>
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
int i, status; //pid_t data type is signed interger type repesenting process ID
pid_t pid; //time_ t data type used to storeing system time value
time_t currentTime;//times() stores the current process time in the struct tms that //that buffer
points to.
struct tms cpuTime;
if((pid = fork())==-1) //start child process
{
perror("\nfork error");
exit(EXIT_FAILURE);
}
else if(pid==0) //child process
{
time(&currentTime); // gives normal time
printf("\nChild process started at %s",ctime(&currentTime));
for(i=0;i<5;i++)
{
printf("\nCounting= %dn",i); //count for 5 seconds
sleep(1);
}
time(&currentTime);
printf("\nChild process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
}
else
{ //Parent process
time(&currentTime);
printf("\nParent process started at %s ",ctime(&currentTime));
if(wait(&status)== -1) //wait for child process
perror("\n wait error");
if(WIFEXITED(status))
printf("\nChild process ended normally.........\n");
else
printf("\nChild process did not end normally");
if(times(&cpuTime)<0) //Get process time
perror("\nTimes error");
else
{ // _SC_CLK_TCK: system configuration time: seconds clock tick
printf("\nParent process user time= %fn",((double) cpuTime.tms_utime));
printf("\nParent process system time = %fn",((double) cpuTime.tms_stime));
printf("\nChild process user time = %fn",((double) cpuTime.tms_cutime));
printf("\nChild process system time = %fn",((double) cpuTime.tms_cstime));
}
time(&currentTime);
printf("\nParent process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
}
}
