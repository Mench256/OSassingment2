#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

struct indexes{
    int start;
    int end;
    char** names;
    int* nums;
};

void* threadFunction(void* val){

    printf("Threads Runnning......\n");

    struct indexes* thread = (struct indexes*)val;
    int start = thread->start;
    int end = thread->end;
    int* nums = thread->nums;
    char** names = thread->names;


    for(int i = start; i < end - 1; i++){
        for(int j = i + 1; j < end; j++){

            if(nums[i] > nums[j]){
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;

            char* tempStr = names[i];
            names[i] = names[j];
            names[j] = tempStr;

            }


        }
    }
    return NULL;
}

int main(){

    int nums[SIZE];
    char* names[SIZE];
    int n = 0;

    pthread_t t[4];
    struct indexes indexes[4];

    int block = 2500;

    FILE* fp = fopen("data.csv", "r");

    char line[256];

    if(fp == NULL){
        printf("Unable to open file!\n");
    }
    else{
        printf("File Opened Successfully!\n");

        while(fgets(line, sizeof(line), fp)){
            char* token = strtok(line, ",");
            char* token2 = strtok(NULL, "\n");
            int value = atoi(token2);

            names[n] = strdup(token);
            nums[n] = value;
            n++;

        }
    
        for(int i = 0; i < 4; i++){

            indexes[i].start = i * block;
            indexes[i].end = (i + 1) * block;
            indexes[i].nums = nums;
            indexes[i].names = names;

            int result = pthread_create(&t[i], NULL, threadFunction, &indexes[i]);

            if(result != 0){

                printf("Error creating thread!\n");
                exit(1);

            }
        }

            for(int i = 0; i < 4; i++){
                pthread_join(t[i], NULL);
            }

    }


    FILE* out  = fopen("thread_sorted.csv", "w");

    if(out == NULL){
        printf("Unable to open output file!\n");
    }
    else{
        printf("Output file opened successfully!\n");
    }

    for(int i = 0; i < n; i++){
        fprintf(out, "%s,%d\n", names[i], nums[i]);
        
    }

    fclose(out);
    fclose(fp);






    return 0;
}