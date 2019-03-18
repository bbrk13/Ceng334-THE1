#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
int main (int argc,char* argv[] )
{
	int N;
	int counter = 0;
	N = atoi(argv[1]);
	if (argc == 3 )
	{
		int i,status,y,k, fd[N][2];
		printf("N is : %d, Parent Process Id: %d\n",N,getpid() );
		for (k = 0; k< N ;k++)
		{
			pipe(fd[k]);
		}
		for (i = 0; i<N;i++)
		{
		y = fork();
			if (y == 0)
			{	/* CHILD*/
				char* buf[1024];
				close(fd[i][1]);
				//dup2(0,fd[i][0]);
				int childcounter  = counter/N;
				for (int t = 0;t<childcounter+1;t++){
					read(fd[i][0],buf,1024);
					char* args[] = {"./WC_Mapper","< ../input/input.txt", NULL };
					execv("./WC_Mapper",args);
					printf("process %d, childcount = %d,counter = %d,counter / N = %d string in child: %s \n",getpid(),childcounter,counter,counter/N,buf );
					}
				close(fd[i][0]);
				exit(0);
			}
			else{
				/*PARENT*/
				close(fd[0][0]);
				char buf[1024];
				int childcount = 0;
				while (fgets(buf,1024,stdin))
				{
					counter++;
					write(fd[childcount][1],buf,1024);
					childcount++;
					childcount = childcount % N ;
					memset(buf,0,sizeof buf);
				//	printf("childcount = %d \n", childcount);
				
				}
				waitpid(y,&status,WEXITED);
				close(fd[0][1]);
			}
		}
	}
	else if (argc == 4)
	{
		printf("this should be a mapReduce model\n");
	}
	return 0;
}
