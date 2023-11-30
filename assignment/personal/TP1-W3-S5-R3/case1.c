#include <stdio.h>
#include <string.h>

void header() {
    printf("*******************************\n");
    printf("* Program konversi jarak x Km *\n");
    printf("* kedalam km, m, dan cm       *\n");
    printf("*******************************\n");
}

int main() {
    header();
    double length;
    printf("\nInput Jarak dalam Km: ");
    scanf ("%lf", &length);

    double km = length;
    int meter = length * 1000;
    int centimeter = meter * 100;

    printf("\n%.2lf km = %d m = %d cm", km, meter, centimeter);

    return 0;
}
