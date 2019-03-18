#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define R 0
#define W 1

void run_child(int in){
    int r;
    char it[1024];
    while((r = read(in, it, sizeof(it))) != 0){
        if(r == -1){
            perror("read");
            exit(1);
        }
        printf("child writes :%s\n",it );
	char *args = {"< ../input/input.txt"};
        execl("./WC_Mapper",it);
        exit(1);
    }
}
int main(int argc, char **argv) {
    // Process fan
    int i;
    int n;
    int num_kids;
    int from_parent[2];
    if(argc != 2) {
        fprintf(stderr, "Usage: fan_write <numkids>\n");
        exit(1);
    }
    num_kids = atoi(argv[1]);
    int status;
    char word[32];
    for(i = 0; i < num_kids; i++) {
        if(pipe(from_parent) == -1){
            perror("pipe");
            exit(1);
        }
        char buf[1024];
        //while (buf[0] !=EOF)
        //{
                 //}
        n = fork();
        if(n < 0) {
            perror("fork");
            exit(1);
        }
        if(n == 0){//child
            if(close(from_parent[W]) == -1){
                perror("close");
                exit(1);
            }
            run_child(from_parent[R]);

            if(close(from_parent[R]) == -1){
                perror("close");
                exit(1);
            }
            exit(0);
        }
        else{ // parent
           fgets(buf, 1024, stdin);
          write(from_parent[W], &buf, sizeof(buf));

        }
    }
    for(i = 0; i < num_kids; i++){
        wait(&status);
    }
    return 0;
}
