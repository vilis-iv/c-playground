#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***********************
* struct for Book
************************/
struct Book {
    int bookId;
    char name[256];
    char category[256];
    char price[256];
};


/***********************
* function to insert book
************************/
void inputBook(struct Book *book, int index) {
    char name[256];
    char category[256];
    char price[256];
    
    
    book[index].bookId = index;         //create book id
    printf("Name: ");
    scanf("%s", book[index].name);      //input book name
    printf("Categories: ");
    scanf("%s", book[index].category);  //input book category
    printf("Price: ");
    scanf("%s", book[index].price);     //input book price

}


/***********************
* function to view book data from input
************************/
void viewData(struct Book *book, int index) {
    for (int i = 0; i < index; i++) {
        printf("\nindex: %d\n", i + 1);
        printf("name: %s\n", book[i].name);
        printf("category: %s\n", book[i].category);
        printf("price: %s\n", book[i].price);
    } 
}

/***********************
* function to delete book data from input
************************/
void deleteData(struct Book *book, int index) {
    viewData(book, index);              //view all book
    int id;
    printf("Select Id:");
    scanf("%d", &id);                   //select index of book to delete
    
    if (id < 0 || id > index) {
        printf("\nindex can not be found\n");
    } else {
         for(int i=id-1; i<index-1; i++)
        {
            book[i] = book[i + 1];      //replace selected book with next iteration of book to delete it 
        }
    }
}


/***********************
* function to save book data
************************/
void saveData(struct Book *book, int index) {
    FILE *pFile;
    pFile = fopen("databuku.txt", "a");                         //append data if file exist

    if (pFile == NULL) pFile = fopen("databuku.txt", "w");      //create data if file does not exist
    else
    for (int i = 0; i < index; i++) {

        char id[10];
        sprintf(id, "%d", book[i].bookId);                      //parse string id to integer
        
        fputs(id, pFile);                                       //put id into file
        fputs("\n", pFile);
        fputs(book[i].name, pFile);
        fputs("\n", pFile);                                     //put name into file
        fputs(book[i].category, pFile);
        fputs("\n", pFile);                                     //put category into file
        fputs(book[i].price, pFile);
        fputs("\n", pFile);                                     //put price into file
    }
        fclose(pFile);
}


/***********************
* load data from file into struct of Book
************************/
int loadFile(struct Book *book) {
    FILE *pFile;
    pFile = fopen("databuku.txt", "r");                         //read the file

    char bookId[256];
    char name[256];
    char category[256];
    char price[256];

    int index = 0;

    if (pFile == NULL) perror("Failed to open file");
    else {
        while (!feof(pFile)) {
            fscanf(pFile, "%s", bookId);                    //bind data into bookId
            fscanf(pFile, "%s", name);                      //bind data into name
            fscanf(pFile, "%s", category);                  //bind data into category
            fscanf(pFile, "%s", price);                     //bind data into price
            int id;
            sscanf(bookId, "%d", &id);                      //parse string id into integer id

            book[index].bookId = id;                        //set id into struct
            strcpy(book[index].name, name);                 //set name into struct
            strcpy(book[index].category, category);         //set category into struct 
            strcpy(book[index].price, price);               //set price into struct
            
            index++;
        }
    }
    return index;
}

/***********************
* view data from file
************************/
void viewFile(struct Book *book, int itemCount) {
    for (int i = 0; i < itemCount - 1; i++) {
        printf("book id: %d\n", book[i].bookId);
        printf("name: %s\n", book[i].name);
        printf("category: %s\n", book[i].category);
        printf("price: %s\n", book[i].price);
    }
}

int main() {
    int i = 0;
    int index = 0;                      //count item for array of struct book
    // FILE *in;
    struct Book *book;                  //struct book to hold input value
    struct Book *file;                  //struct file to hold file value
    book = malloc(sizeof(struct Book));      //allocate memory for book
    file = malloc(sizeof(struct Book));      //allocate memory for file
    
    while (i != 6) {                         //check to stop application when menu 6. exit is selected
    printf("===============BOOK STORE==================\n");
    printf("1. Input\n");
    printf("2. View History\n");
    printf("3. View Book\n");
    printf("4. Delete History\n");
    printf("5. Delete Book\n");
    printf("6. Exit\n");
    printf("\nSelect Option: ");
    scanf("%d", &i);
    getchar();
    
    int itemCount = loadFile(file);         //count item to define array of struct item size
    
    switch (i) {
        case 1 : printf("Input Book\n");
        inputBook(book, index);
        index++;                            //increase index for array of book size
        break;

        case 2 : printf("View History\n");
        viewData(book, index);
        break;
        
        case 3 : printf("View Book\n");
        viewFile(file, itemCount);
        break;

        case 4 : printf("delete history\n");
        deleteData(book, index);
        index--;                            //decrease index for array of book size
        break;
        case 5 : printf("delete book\n");
        deleteData(file, itemCount);
        itemCount--;
        break;
        case 6 : printf("exit\n");
        saveData(file, index);
        break;
        }
    }
    return 0;
}