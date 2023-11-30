#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void header() {
    printf("*******************************\n");
    printf("* Program Penghitung Total    *\n");
    printf("* Belanja                     *\n");
    printf("*******************************\n");
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
        transactions = realloc(transactions, (index + 1) * sizeof(struct trx));
        printf("\nBulan Belanja (1-12): ");
        scanf("%d", &transactions[index].month);
        printf("Total Belanja Rp: ");
        scanf ("%lf", &transactions[index].fPrice);
        transactions[index].deleted = false;
        getchar();

        
        int totalGroceriesInMonth = 0;
        for(int i = 0; i < index + 1; i++) {
            if(transactions[index].month == transactions[i].month && !transactions[i].deleted) {
                totalGroceriesInMonth++;
            }
        }

        if(totalGroceriesInMonth == 4) {
            for(int i = 0; i < index; i++) {
                if(transactions[index].month == transactions[i].month && !transactions[i].deleted) {
                    transactions[i].deleted = true;
                }
            }
        }

        index++;
        printf("TOTAL GROCERIES: %d", totalGroceriesInMonth);
        nextEntry(isEntry);
    }

    for(int i = 0; i < index; i++) {
        printf("\n%.2lf",transactions[i].fPrice);
    }

    
    return 0;
}