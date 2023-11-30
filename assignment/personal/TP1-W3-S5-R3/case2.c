#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void header() {
    printf("*******************************\n");
    printf("* Program Penghitung Total    *\n");
    printf("* Belanja & Diskon            *\n");
    printf("*******************************\n");
}

void footer(int totalGroceries, double basePrice, double price, char discountTag[10]) {
    printf("\nOUTPUT: ");
    printf("\nTotal Belanja Bulan Ini: %d", totalGroceries);
    printf("\nJumlah Diskon: %s", discountTag);
    printf("\nHarga Asli: Rp %.2lf", basePrice);
    printf("\nHarga Setelah Diskon: Rp %.2lf", price);
    printf("\n*********************************************\n");

}

struct trx {
    double fPrice;      //Final Price after discount
    int month;
    bool deleted;
};

void nextEntry(char *isEntry) {
        printf("\ncontinue (Y/n): ");
        fgets(isEntry, 10, stdin);
        isEntry[strcspn(isEntry, "\n")] = '\0';
}

int main() {
    /********************
    * PROGRAM TITLE
    *********************/
    header();
    /**************************
     * Variables
     **************************/
    struct trx *transactions;
    transactions = malloc(sizeof(struct trx));
    char isEntry[] = "Y";
    double price;
    int month;
    int index = 0;

    /********************************
    * While Loop to keep user always able to enter data 
    * unless choosing 'N' or 'n' when choosing "continue (Y/n): "
    *********************************/
    while(strcmp(isEntry, "N") != 0 && strcmp(isEntry, "n") != 0) {
        double price;
        double basePrice;
        char discountTag[10];
        transactions = realloc(transactions, (index + 1) * sizeof(struct trx));
        printf("\nINPUT: ");
        printf("\nBulan Belanja (1-12): ");
        scanf("%d", &transactions[index].month);
        printf("Total Belanja Rp: ");
        scanf ("%lf", &transactions[index].fPrice);
        getchar();
        
        price = transactions[index].fPrice;
        basePrice = price;
        if (price < 200000) {
            // discountTag = "0%";
            strcpy(discountTag, "0%");
            price = price;
        } 
        else if (price >= 200000 && price < 550000) {
            // discountTag = "10%";
            strcpy(discountTag, "10%");
            price = price - (price * 10 / 100);
        } 
        else if (price >= 550000 && price < 1000000) {
            // discountTag = "20%";
            strcpy(discountTag, "20%");
            price = price - (price * 20 / 100);
        }
        else {
            // discountTag = "30%";
            strcpy(discountTag, "30%");
            price = price - (price * 30 / 100);
        }

        transactions[index].deleted = false;

        int totalGroceriesInMonth = 0;
        for(int i = 0; i < index + 1; i++) {
            if(transactions[index].month == transactions[i].month && !transactions[i].deleted) {
                totalGroceriesInMonth++;
            }
        }

        if(totalGroceriesInMonth == 4) {
            char extraDiscountTag[] = " + 20%";
            strcat(discountTag, extraDiscountTag);
            for(int i = 0; i < index + 1; i++) {
                if(transactions[index].month == transactions[i].month && !transactions[i].deleted) {
                    transactions[i].deleted = true;
                    price = price - (price * 20 / 100);
                }
            }
        }

        index++;
        footer(totalGroceriesInMonth, basePrice, price, discountTag);
        nextEntry(isEntry);
    }

    for(int i = 0; i < index; i++) {
        printf("\n%d", transactions[i].month);
        printf("\n%.2lf",transactions[i].fPrice);
        printf("\n%s", transactions[i].deleted ? "true" : "false");
    }

    
    return 0;
}