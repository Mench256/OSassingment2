#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* threadFunction(void* val){

    printf("Threads Runnning......\n");
    return NULL;
}

int main(){

    pthread_t t[4];
    
    for(int i = 0; i < 4; i++){
        int result = pthread_create(&t[i], NULL, threadFunction, NULL);

        if(result != 0){

            printf("Error creating thread!\n");
            exit(1);

        }
    }

    for(int i = 0; i < 4; i++){
        pthread_join(t[i], NULL);
    }



    return 0;
}