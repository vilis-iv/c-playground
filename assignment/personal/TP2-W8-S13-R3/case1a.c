#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************
* structure of 'months' to contain month data 
*****************************/
struct months {
    char name[9];               //Name of the month
    int vocal;                  //Number of vocal letter
    int nonVocal;               //Number of non-vocal letter
};


/****************************
* Function to count vocal letter
* @Param String of month name
* @Return int of vocal letter count 
*****************************/
int countVocal(char *monthName) {
    int index = 0;                          //index to count vocal letter on month name
    char vocalChar[5] = "aiueo";            //array of vocal letter

    for (int i = 0; i < strlen(monthName); i++) {       //Iterate each letter from month name
        for(int j = 0; j < 5; j++) {                    //Iterate each letter from vocal char
            if (tolower(monthName[i]) == vocalChar[j])  //Using tolower() function to convert uppercase letter to lowercase 
                 index++;                               //then compare it with list of vocal char, increase the value of index when the char are equal
        }
    }
    return index;  
}

void populateMonth(struct months *months) {
    char *monthsData[12] = {"Januari", "Februari", "Maret"              //Arrays of months
                            , "April", "Mei", "Juni"
                            , "Juli", "Agustus", "September"
                            , "Oktober", "November", "Desember"};

    for(int i = 0; i < sizeof(monthsData)/sizeof(monthsData[0]); i++) {
        strcpy(months[i].name, monthsData[i]);                          //Insert month name 
        months[i].vocal = countVocal(monthsData[i]);                    //Insert vocal count
        months[i].nonVocal = strlen(monthsData[i]) - months[i].vocal;   //Insert non-vocal count
    }
}

int main() {
    struct months months[12];
    struct months *result;
    int index = 0;
    char letter;
    populateMonth(months);

    printf("\n**************INPUT***************\n");
    printf("Enter letter : ");
    scanf("%c", &letter);

    result = malloc(sizeof(struct months));                 //Allocating memory for array result
    for (int i = 0; i < 12; i++) {
        if (toupper(letter) == months[i].name[0]) {         //Compare input char with the first letter of month name
            printf("%d. %s\n", index + 1, months[i].name);  //Print result list

            result = realloc(result, (index + 1) * sizeof(struct months));  //Reallocate memory to contain dynamic array based on result size
            strcpy(result[index].name, months[i].name);     //map the months struct into result struct
            result[index].vocal = months[i].vocal;
            result[index].nonVocal = months[i].nonVocal;
            index++;
        }
    }

    printf("Select month (number) : ");
    scanf("%d", &index);
    
    printf("\n**************RESULT***************\n");
    printf("%s\n", result[index - 1].name);
    printf("vocal: %d\n", result[index - 1].vocal);
    printf("non-vocal: %d\n", result[index - 1].nonVocal);
    getchar();
    return 0;
}