#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/****************************
* structure of 'trx' to contain transaction data consisting of different data types 
*****************************/
struct trx {
    double fPrice;      //Final Price after discount
    int month;          //Month of Transaction
    bool deleted;       //Data deletion distinction
};

/****************************
* Function Description: creating terminal line prompt to get user's confirmation wether to continue to enter next transaction or stop the program
*
* @input: String isEntry
*****************************/
void nextEntry(char *isEntry) {
        printf("\ncontinue (Y/n): ");
        fgets(isEntry, 10, stdin);
        isEntry[strcspn(isEntry, "\n")] = '\0';
}

/****************************
* Function Description: Print Program title at the top line of terminal
* 
* @output: print line of program title
*****************************/
void header() {
    printf("*******************************\n");
    printf("* Program Penghitung Total    *\n");
    printf("* Belanja & Diskon            *\n");
    printf("*******************************\n");
}

/****************************
* Function Description: Print Program output for each iteration of transaction entered
*
* @input: int totalGroceries, double basePrice, double price, String discountTag
* @output: print line of transaction detail
*****************************/
void footer(int totalGroceries, double basePrice, double price, char discountTag[10]) {
    printf("\nOUTPUT: ");
    printf("\nTotal Belanja Bulan Ini: %d", totalGroceries);
    printf("\nJumlah Diskon: %s", discountTag);
    printf("\nHarga Asli: Rp %.2lf", basePrice);
    printf("\nHarga Setelah Diskon: Rp %.2lf", price);
    printf("\n*********************************************\n");

}


int main() {
    header();                                       //Program Title
    
    struct trx *transactions;                       //initializing struct trx as transactions
    transactions = malloc(sizeof(struct trx));      //allocating memory for transactions
    char isEntry[] = "Y";                           //initializing isEntry to check wether to continue or stop the program
    int index = 0;                                  //index to help iteration inside while loop

    /********************************
    * While Loop for user to be able to continously enter data 
    * unless choosing 'N' or 'n' to stop entry and close the program
    *********************************/
    while(strcmp(isEntry, "N") != 0 && strcmp(isEntry, "n") != 0) {

        /********************************
        * re-allocating memory with the help of index to initialize array's size of transactions 
        * and to create a dynamic array for transactions when user decided to continue the program
        *********************************/
        transactions = realloc(transactions, (index + 1) * sizeof(struct trx));     

        double basePrice;                           //Actual Price
        double price;                               //Discounted Price
        char discountTag[10];                       //Discount Tag eg: "20%" or "30% + 20%"
        printf("\nINPUT: ");
        printf("\nBulan Belanja (1-12): ");
        scanf ("%d", &transactions[index].month);
        printf("Total Belanja Rp: ");
        scanf ("%lf", &transactions[index].fPrice);
        getchar();                                  //getchar() to clean trailing "\n" after scanf in order to not distrupt fgets inside nextEntry function
        transactions[index].deleted = false;        //Set deleted status to false for new input
        

        price = transactions[index].fPrice;
        basePrice = price;
        if (price < 200000) {
            strcpy(discountTag, "0%");
            price = price;
        } 
        else if (price >= 200000 && price < 550000) {
            strcpy(discountTag, "10%");
            price = price - (price * 10 / 100);
        } 
        else if (price >= 550000 && price < 1000000) {
            strcpy(discountTag, "20%");
            price = price - (price * 20 / 100);
        }
        else {
            strcpy(discountTag, "30%");
            price = price - (price * 30 / 100);
        }


        /**************************************
        * Check for total transaction with deleted status set to false on given month
        * 'totalGroceries' will increase for each iteration from 'struct trx transactions' that match the same month as the input
        ***************************************/
        int totalGroceries = 0;
        for(int i = 0; i < index + 1; i++) {
            if(transactions[index].month == transactions[i].month && !transactions[i].deleted) {
                totalGroceries++;
            }
        }

        /**************************************
        * if 'totalGroceries' reach 4 or equal to 4 apply additional discount to current transaction, 
        * and set the status of 4 prevous transactions to deleted, so it will not iterated again in the next transaction
        ***************************************/
        if(totalGroceries == 4) {
            char extraDiscountTag[] = " + 20%";     //Extra discount tag
            strcat(discountTag, extraDiscountTag);  //Append discount tag with extra discount tag
            price = price - (price * 20 / 100);     //Add extra discount to previous discount
            
            for(int i = 0; i < index + 1; i++) {
                if(transactions[index].month == transactions[i].month && !transactions[i].deleted) {
                    transactions[i].deleted = true;
                }
            }
        }

        index++;

        footer(totalGroceries, basePrice, price, discountTag);  //Set Output
        nextEntry(isEntry);                                     //Display confirmation prompt
    }

    return 0;
}