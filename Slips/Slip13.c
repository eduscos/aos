q1)
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main ()
{
int pid1;
int pid2;
pid1 = fork();
if (pid1 == 0) /* First child */
{
while (1) /* Infinite loop */
{
printf ("P1 is alive\n");
sleep (1);
}
}
pid2 = fork (); /* Second child */
if (pid2 == 0)
{
while (1) /* Infinite loop */
{
printf ("P2 is alive\n");
sleep (1);
}
}
sleep (3);
kill (pid1, SIGSTOP); /* Suspend first child */
sleep (3);
kill (pid1, SIGCONT); /* Resume first child */
sleep (3);
kill (pid1, SIGINT); /* Kill first child */
kill (pid2, SIGINT); /* Kill second child */
}



q2)
#include<stdio.h>
#include<dirent.h>
#include<string.h>
int main(int argc, char* argv[])
{
DIR *d;
char *position;
struct dirent *dir;
int i=0;
if(argc!=2){
printf("Provide suffiecient args");
}
else {
d = opendir(".");
if (d)
{
while ((dir = readdir(d)) != NULL)
{
position=strstr(dir->d_name,argv[1]);
i=position-dir->d_name;
if(i==0)
printf("%s\n",dir->d_name);
}
closedir(d);
}
return(0);
}
}
