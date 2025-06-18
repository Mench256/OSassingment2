// Abraham Menchaca, 1002167812, CSE3320-002


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Change this for number of processes
int numOfProcesses = 10;

int main(){


    for(int i = 0; i < numOfProcesses; i++){
    pid_t pid = fork();

    // Checking if in child
    if(pid == 0){
    
    
    char block[12];
    snprintf(block, sizeof(block), "%d", i);

    char input[] = "data.csv";

    char output[64];
    snprintf(output, sizeof(output), "sorted%d.csv", i);

    // Calling execl to replace child
    execl("./driver", "driver", block, input, output, NULL);
    // Error Checking
    perror("exec failed!");
    exit(1);

    }

    else if(pid < 0){
        perror("Fork Unsuccessful!\n");
        exit(1);
    }

    }
    // Making sure processes wait
    for(int i = 0; i < numOfProcesses; i++){
        wait(NULL);
    }


    return 0;
}