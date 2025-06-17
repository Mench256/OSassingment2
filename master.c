// Abraham Menchaca, 1002167812


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

    // This loop controls the number of processes made
    for(int i = 0; i < 4; i++){
    pid_t pid = fork();

    if(pid == 0){

    char block[10];
    sprintf(block, "%d", i);

    char input[] = "data.csv";
    char output[50];
    sprintf(output, "sorted%d.csv", i);

    execl("./driver", "driver", block, input, output, NULL);

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