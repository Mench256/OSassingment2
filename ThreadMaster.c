// Abraham Menchaca, 1002167812, CSE3320-002

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

// Struct for indexes
struct indexes{
    int start;
    int end;
    char** names;
    int* nums;
};
// Change this for number of threads
int numOfThreads = 10;

void* threadFunction(void* val){

    printf("Threads Runnning......\n");
    // Setting values
    struct indexes* thread = (struct indexes*)val;
    int start = thread->start;
    int end = thread->end;
    int* nums = thread->nums;
    char** names = thread->names;

    // Sorting logic
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

    pthread_t t[numOfThreads];
    struct indexes indexes[numOfThreads];

    int block = 10000 / numOfThreads;

    // Opening File
    FILE* fp = fopen("data.csv", "r");

    char line[256];

    // Checking if open succesfully
    if(fp == NULL){
        printf("Unable to open file!\n");
    }
    else{
        printf("File Opened Successfully!\n");

        // While loop reading file
        while(fgets(line, sizeof(line), fp)){
            // Spliting strings
            char* token = strtok(line, ",");
            char* token2 = strtok(NULL, "\n");
            int value = atoi(token2);
            // Putting in respected arrays
            names[n] = strdup(token);
            nums[n] = value;
            n++;

        }
    
        for(int i = 0; i < numOfThreads; i++){

            // Setting indexes
            indexes[i].start = i * block;
            indexes[i].end = (i + 1) * block;
            indexes[i].nums = nums;
            indexes[i].names = names;

            // Creating threads
            int result = pthread_create(&t[i], NULL, threadFunction, &indexes[i]);
            // Checking if they were made properly
            if(result != 0){

                printf("Error creating thread!\n");
                exit(1);

            }
        }
            // Joining threads
            for(int i = 0; i < numOfThreads; i++){
                pthread_join(t[i], NULL);
            }

    }

    // Opening output file
    FILE* out  = fopen("thread_sorted.csv", "w");
    // Checking if file opened 
    if(out == NULL){
        printf("Unable to open output file!\n");
    }
    else{
        printf("Output file opened successfully!\n");
    }
    // Writing data to file
    for(int i = 0; i < n; i++){
        fprintf(out, "%s,%d\n", names[i], nums[i]);
        
    }
    // Closing Files
    fclose(out);
    fclose(fp);






    return 0;
}