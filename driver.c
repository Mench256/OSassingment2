// Abraham Menchaca
// github link: https://github.com/Mench256/OSassingment2.git

// I HAVE GLOBAL VARIABLES AT TOP THAT DETERMINE NUMBER OF PROCESSES OR THREADS CHOSEN BY USER

// sites used
// https://www.geeksforgeeks.org/c/read-a-file-line-by-line-in-c/
// https://www.geeksforgeeks.org/c/how-to-split-a-string-by-a-delimiter-in-c/
// https://www.youtube.com/watch?v=xoXzp4B8aQk
// https://stackoverflow.com/questions/35403892/creating-threads-in-a-loop
// https://www.geeksforgeeks.org/c/understanding-extern-keyword-in-c/
// https://www.youtube.com/watch?v=T91q6ZngBk4

// TO COMPILE:
// ------------------
// For part 1:
// gcc -o driver driver.c
// gcc -o master master.c
// ./master

// For part 2:
// gcc -o ThreadMaster ThreadMaster.c
// ./ThreadMaster




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10000

// Global Variable
int n = 0;
// Change this for number of processes
int numOfProcesses = 10;

int main(int argc, char* argv[]){


    int nums[SIZE];
    char* names[SIZE];
    
    // Opening file for reading
    FILE* fp = fopen(argv[2], "r");

    char line[256];
    // Checking if file opened properly
    if(fp == NULL){
        printf("Unable to open file!\n");
    }
    else{
        printf("File Opened Successfully!\n");
        // Using while loop to read lines
        while(fgets(line, sizeof(line), fp)){
            // Spliting strings
            char* token = strtok(line, ",");
            char* token2 = strtok(NULL, "\n");
            int value = atoi(token2);
            // Inputing data into respected arrays
            names[n] = strdup(token);
            nums[n] = value;
            n++;

        }
        // Closing file
        fclose(fp);
    }
    // Setting indexes
    int size = 10000 / numOfProcesses;
    int index = atoi(argv[1]);
    int start = index * size;
    int end = start + size;
    // Sorting both arrays
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
    // Opening output file to write
    FILE* out  = fopen(argv[3], "w");
    // Checking if file opened properly
    if(out == NULL){
        printf("Unable to open output file!\n");
    }
    else{
        printf("Output file opened successfully!\n");
    }
    // Writing data to file
    for(int i = start; i < end; i++){
        fprintf(out, "%s,%d\n", names[i], nums[i]);
        
    }
    // Closing output file
    fclose(out);

 



    return 0;
}
