#include <stdio.h>
#include <string.h>

void reverseInput(int num){
    int a, rev = 0, c = 0;

     do {
        int rem = 0;
        rem = a%10;
        a = a/10;
        rev = rev*10+rem;

     }while(num > 0);

     printf("Print reverse : %d", rev);
}

int main() {

    int inputFromUser = 0;

    printf("Enter positive integer");
    scanf("%d", &inputFromUser);

    reverseInput(inputFromUser);


    return 0;
}
