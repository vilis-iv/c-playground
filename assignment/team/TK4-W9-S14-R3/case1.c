#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookId;
    char name[256];
    char category[256];
    char price[256];
};

void inputBook(struct Book *book, int index) {
    char name[256];
    char category[256];
    char price[256];
    
    // book = realloc(book, (index + 1) * sizeof(struct Book));     
    
    book[index].bookId = index;
    printf("Name: ");
    scanf("%s", book[index].name);
    printf("Categories: ");
    scanf("%s", book[index].category);
    printf("Price: ");
    scanf("%s", book[index].price);

}

void viewData(struct Book *book, int index) {
    for (int i = 0; i < index; i++) {
        printf("\nname: %s\n", book[i].name);
        printf("category: %s\n", book[i].category);
        printf("price: %s\n", book[i].price);
    } 
}

void deleteData(struct Book *book, int index) {
    viewData(book, index);
    int id;
    printf("Select Id:");
    scanf("%d", &id);
    
    if (id < 0 || id > index) {
        printf("\nindex can not be found\n");
    } else {
         for(int i=id-1; i<index-1; i++)
        {
            book[i] = book[i + 1];
        }
    }
}

void saveData(struct Book *book, int index) {
    FILE *pFile;
    pFile = fopen("databuku.txt", "a");
    for (int i = 0; i < index; i++) {

        char id[10];
        sprintf(id, "%d", book[i].bookId);
        
        fputs(id, pFile);
        fputs("\n", pFile);
        fputs(book[i].name, pFile);
        fputs("\n", pFile);
        fputs(book[i].category, pFile);
        fputs("\n", pFile);
        fputs(book[i].price, pFile);
        fputs("\n", pFile);
    }
        fclose(pFile);
}

void viewFile(struct Book *book) {
    FILE *pFile;
    pFile = fopen("databuku.txt", "r");

    char bookId[256];
    char name[256];
    char category[256];
    char price[256];

    int index = 0;

    if (pFile == NULL) perror("Failed to open file");
    else {
        while (!feof(pFile)) {
            fscanf(pFile, "%s", bookId);
            fscanf(pFile, "%s", name);
            fscanf(pFile, "%s", category);
            fscanf(pFile, "%s", price);
            int id;
            sscanf(bookId, "%d", &id);

            book[index].bookId = id;
            strcpy(book[index].name, name);
            
            index++;
            printf("book id: %s\n", bookId);
            printf("name: %s\n", name);
            printf("category: %s\n", category);
            printf("price %s\n", price);
        }
    }

    for (int i = 0; i < index; i++) {

    }
}

int main() {
    int i = 0;
    int index = 0;
    // FILE *in;
    struct Book *book;
    struct Book *file;
    book = malloc(sizeof(struct Book));      
    file = malloc(sizeof(struct Book));      
    
    while (i != 6) {
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
    
    switch (i) {
        case 1 : printf("Input Book\n");
        inputBook(book, index);
        index++;
        break;

        case 2 : printf("View History\n");
        viewData(book, index);
        break;
        
        case 3 : printf("View Book\n");
        // viewData(book, index);
        viewFile(file);
        break;

        case 4 : printf("delete history");
        deleteData(book, index);
        index--;
        break;
        case 5 : printf("delete book");
        break;
        case 6 : printf("exit\n");
        saveData(book, index);
        break;
        }
    }
    return 0;
}