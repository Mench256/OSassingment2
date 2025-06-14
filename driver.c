#include <stdio.h>
#define SIZE 10000




int main(){

    int nums[SIZE];
    char* names[SIZE];


    for(int i = 0; i < SIZE - 1; i++){
        for(int j = i + 1; j < SIZE; j++){
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;

            char* tempStr = names[i];
            names[i] = names[j];
            names[j] = tempStr;


        }
    }

    return 0;
}