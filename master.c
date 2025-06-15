// Abraham Menchaca, 1002167812


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){


    for(int i = 0; i < 4; i++){
    pid_t pid = fork();

    if(pid == 0){

    char input[50];
    char output[50];
    sprintf(input, "data.csv");
    sprintf(output, "sorted%d.csv", i);

    execl("driver", "driver", input, output, NULL);

    perror("exec failed!");
    exit(1);

    }

    else if(pid < 0){
        perror("Fork Unsuccessful!\n");
        exit(1);
    }

    }

    for(int i = 0; i < 4; i++){
        wait(NULL);
    }


    return 0;
}