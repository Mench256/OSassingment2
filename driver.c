// Abraham Menchaca, 1002167812

// sites used
// https://www.geeksforgeeks.org/c/read-a-file-line-by-line-in-c/

/*
int chunk_index = atoi(argv[1]);  // 0 to 3
int chunk_size = 10000 / 4;
int start = chunk_index * chunk_size;
int end = start + chunk_size;
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10000


int n = 0;

int main(int argc, char* argv[]){


    int nums[SIZE];
    char* names[SIZE];
    int processes = 4;

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

           // printf("%s | %d\n", token, value);
        }
        fclose(fp);
    }

    int index = atoi(argv[1]);
    int start = index * 2500;
    int end = start + 2500;

    for(int i = start; i < end - 1; i++){
        for(int j = i + 1; j < end; j++){

            if(nums[i] > nums[j]){
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;

            char* tempStr = names[i];
            names[i] = names[j];
            names[j] = tempStr;


           //printf("names[%d]: %s | nums[%d]: %d\n", i, names[i], i, nums[i]);
            }


        }
    }

    FILE* out  = fopen(argv[2], "w");

    if(out == NULL){
        printf("Unable to open output file!\n");
    }
    else{
        printf("Output file opened successfully!\n");
    }

    for(int i = start; i < end; i++){
        fprintf(out, "%s,%d\n", names[i], nums[i]);
        
    }

    fclose(out);

    return 0;
}