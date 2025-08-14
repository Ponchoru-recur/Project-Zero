#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

//  SAM M. VARELA

void calculate(char value[]){
    if (value[0] == '-'){
        printf("Negative value/s are not allowed\n");
        return;
    }

    int storage = 0;
    for (int i = 0; i <= strlen(value); i++){
        storage += (int)value[i] - '0';
    }
    storage = storage * -1;

    printf("The sum of the digits is : %d", storage);
    return;
}

int main() {

    char input[50] = "0";

    printf("Enter a positive integer : ");
    scanf("%s", input);

    calculate(input);


    return 0;
}
