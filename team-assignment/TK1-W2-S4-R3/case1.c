#include <math.h>
#include <stdio.h>
#include <stdbool.h>

/****************************
*Function Description: Check wether the given digit is single or not
*@Input  : int
*@Output : boolean
*****************************/
bool isSingleDigit(int digit) {
    if (digit == 0) digit = 1;
    return (log10(digit) + 1) < 2.0 ? true: false;
}

int main() {
    int input = 72555;
    /****************************
    * Uncomment 2 line below to use input parameter
    *****************************/
    // printf("input second value: ");
    // scanf("%d", &input);

    int time[3];
    time[0] = input / 3600;               //Fetch hours
    time[1] = input % 3600 / 60;          //Fetch minute
    time[2] = input % 3600 % 60;          //Fetch second

    for(int i = 0; i < 3; i++) {
        printf(isSingleDigit(time[i])     //Check wether the value is single digit or not
            ? i != 2 ? "0%d:" : "0%d"     //If the value is single digit add '0' as prefix
            : i != 2 ? "%d:" : "%d"       //else print the exact value
            ,time[i] 
        );
    }

    printf("\n");
    return 0;
}