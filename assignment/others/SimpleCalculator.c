#include <stdio.h>

float calc(char operator, float numX, float numY) {
    float result = 0;
    if(operator == '+') result = numX + numY;
    else if(operator == '-') result = numX - numY;
    else if(operator == '*') result = numX * numY;
    else if(operator == '/') result = numX / numY;
    return result;
}

int main() {
    float num1, num2, num3, result;
    char operator1, operator2;
    
    printf("Equation = ");
    scanf("%f %c %f %c %f", &num1, &operator1, &num2, &operator2, &num3);
    
    result = (operator2 == '*' || operator2 == '/') 
                ? calc(operator1, num1, calc(operator2, num2, num3))
                : calc(operator2, num3, calc(operator1, num1, num2));

    printf("\nResult = %.1f", result);
    return 0;
}
