#include <stdio.h>
#include <string.h>

int main() {
    char strcon[100];
    char str1[100];
    char str2[100];
    char str3[100];
    printf("Kalimat 1 = ");
    scanf("%s", str1);
    printf("Kalimat 2 = ");
    scanf("%s", str2);
    printf("Kalimat 3 = ");
    scanf("%s", str3);
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int str3Len = strlen(str3);


    printf("\nGabungan 3 buah inputan kalimat = ");
    sprintf(strcon, "%s %s %s", str1, str2, str3);  // using function sprintf() to concatenate 3 Strings into one variable named 'strcon' 
    printf("%s", strcon);

    printf("\nHasil membalik kalimat gabungan = ");
    for(int i = strlen(strcon) - 1; i >= 0; i--)            // iterate char array: strcon, using it's length from the highest index meaning the last letter to 0 the first letter  
        printf("%c", strcon[i]);                       // and print each of the chars according to each index to form a reversed sentence

    printf("\nJumlah Huruf kalimat pertama = ");
    printf("%d", str1Len);
    printf("\nJumlah Huruf kalimat kedua = ");
    printf("%d", str2Len);
    printf("\nJumlah Huruf kalimat ketiga = ");
    printf("%d", str3Len);
    printf("\nTotal Jumlah huruf = ");
    printf("%d", str1Len + str2Len + str3Len);
}