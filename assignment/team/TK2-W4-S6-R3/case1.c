#include <stdio.h>

int main() {
    int hours; 
    double costs = 10000;    
    printf("Durasi (Jam): ");
    scanf("%d", &hours);

    costs *= hours;
    if (hours >= 4 && hours < 6) costs -= costs * 10/100;
    else if (hours >= 6 && hours < 8) costs -= costs * 15/100;
    else if (hours == 8) costs -= costs * 20/100;
    else if (hours > 8) costs -= costs * 25/100;

    printf("\nLama pemakaian: %d jam", hours);
    printf("\nBiaya pemakaian: Rp %.2f", costs);
    return 0;
}