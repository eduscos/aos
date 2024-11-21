q1)
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main()
{
int pid;
pid=fork();
if (pid<0)
{
printf("Fork Failed \n");
exit(1);
}
else if(pid==0)
{
execlp("/bin/ls","ls","-l",NULL); // Execute ls
}
else
{
wait(NULL);
printf("\nChild Complete");
exit(0);
}
}


q2)
#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
typedef struct file_info
{
char *name;
size_t size;
}fileinfo;
void insertionSort(fileinfo info[], int n)
{
int i, j;
fileinfo key;
for (i = 1; i < n; i++)
{
key = info[i];
j = i - 1;
while (j >= 0 && info[j].size > key.size)
{
info[j + 1] = info[j];
j = j - 1;
}
info[j + 1] = key;
}
}
void main(int argc, char **argv)
{
struct stat fstat;
if(argc < 3)
{
printf("no files passed\n");
exit(1);
}
int fileCount = argc -1;
fileinfo info[fileCount];
int i;
printf("Display all filenames in ascending order according to their sizes.\n");
for(i =1;i<argc;i++)
{
info[i-1].name = argv[i];
stat(argv[i],&fstat);
info[i-1].size = fstat.st_size;
}
insertionSort(info, fileCount);
for(i=0;i<fileCount;i++)
{
printf("%s -> %ld\n", info[i].name, info[i].size);
}
}
