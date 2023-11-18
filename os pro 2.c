#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
int main(int args,char *ar[])
{
char *source=ar[1];
char *dest="def.txt";
char *buf=(char *)malloc(sizeof(char)*120);
int fd1,fd2;
fd1=open(source,O_CREAT,0744);
fd2=open(dest,O_CREAT,0744);
while(read(fd1,buf,120)!=-1)
{
printf("%s",buf);
write(fd2,buf,120);
}
printf("Process Done");
close(fd1);
close(fd2);
}
