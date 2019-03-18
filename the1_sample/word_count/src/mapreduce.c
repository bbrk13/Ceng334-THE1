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
		//printf("N is : %d, Parent Process Id: %d\n",N,getpid() );
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
				dup2(fd[i][0],0);
				int childcounter  = counter/N;
			//	printf("counter = %d / N = %d = %d \n",counter,N,childcounter );
				if (counter % N == 0){
					if (childcounter == 0 && counter ==0)
						{
				//			printf("expexted case, pid = %d \n", getpid() );
							for (int t = 0; t < 2 ; t++){
							char* args[] = {"./WC_Mapper",NULL  };
							execv("./WC_Mapper",args);
						}
							//exit(1);
						}
						else{
							for (int t = 0;t<childcounter;t++){
							char* args[] = {"./WC_Mapper",NULL /*,"< ../input/input.txt", NULL*/ };
							execv("./WC_Mapper",args);
						}
					}
				}
				else {
					if (i<(counter - N)){
						for (int t = 0;t<childcounter+1;t++){
							char* args[] = {"./WC_Mapper",NULL /*,"< ../input/input.txt", NULL*/ };
							execv("./WC_Mapper",args);
						}
					}
					else{
						for (int t = 0;t<childcounter;t++){
							char* args[] = {"./WC_Mapper",NULL /*,"< ../input/input.txt", NULL*/ };
							execv("./WC_Mapper",args);
							}
						}
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
					//printf("buf = %s\n",buf );
					memset(buf,0,sizeof buf);
				}
				waitpid(y,&status,WEXITED);
				close(fd[0][1]);
			}
		}
	}
	else if (argc == 4)
	{
		//printf("this should be a mapReduce model\n");
	}
	return 0;
}
