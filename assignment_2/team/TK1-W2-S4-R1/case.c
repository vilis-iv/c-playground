/*********************************
* GROUP 6
**********************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct data {
    char productName[35];
    int qty;
    struct data *next, *prev;
} *head, *tail, *curr;

void view() {
    printf("------+-----------------------------------------------+------------\n");
    printf("| No. | Product Name                                  |       Qty |\n");
    printf("------+-----------------------------------------------+------------\n");

    int row = 0;
    curr = head;
    while (curr) {
        row++;
        printf("| %3d | %-45s | %9d | \n", row, curr -> productName, curr -> qty);
        curr = curr -> next;
    
    }
    printf("\n\n\n\n\n");
    
}

void pushHead(char productName[], int qty) {
    curr = (struct data*)malloc(sizeof(struct data));

    strcpy(curr -> productName, productName);
    curr -> qty = qty;

    if (head==NULL) {
        head = tail = curr;
    } else {
        curr -> next = head;
        head -> prev = curr;
        head = curr;
    }

    head -> prev = NULL;
    tail -> next = NULL;
}

void pop(struct data *node) {
    struct data *temp;
    if(head != NULL) {

        if (node == head) {
            head = head -> next;
            free(node);

            if (head != NULL) {
                head -> prev = NULL;
            } else {
                tail = NULL;
            }

        } else if (node == tail) {
            tail = tail -> prev;
            if (tail != NULL) {
                tail -> next = NULL;
            } else {
                head = NULL;
            }
            free(node);
        
        } else {
            node -> prev -> next = node -> next;
            node -> next -> prev = node -> prev;
        }
    }
}

void popAll() {
    while (head != NULL) {
        curr = head;
        head = head -> next;
        free(curr);
    
    }
}

void addProduct() {
    char productName[35];
    int qty;
    printf("\n\n\n");

    do {
        printf("Product name [5..35] characters: ");
        scanf(" %[^\n]", productName);
        fflush(stdin);
    
    } while (strlen(productName)<5 || strlen(productName)>35);

    printf("\n");

    do {
        printf("Product Quantity [1..50]: ");
        scanf("%d", &qty);
        fflush(stdin);
    
    } while (qty<1 || qty>50);

    pushHead(productName, qty);

    printf("Product added\n");
    getchar();
}

void deleteProduct() {
    int total = 0;
    int pos;
    int i;

    if(head == NULL) {
        printf("\n\n\n ------ No Product Data -----\n");

    } else {
        view();
        curr = head;

        while (curr) {
            total++;
            curr = curr -> next;
        }

        printf("\n\n");

        do {
            printf("Input Product Row [1..%d]: ", total);
            scanf("%d", &pos);
            fflush(stdin);
        } while(pos<1 || pos>total);

        curr = head;
        for (i = 1; i < pos; i++) {
            curr = curr -> next;
        }

        pop(curr);
    }
    getchar();
    fflush(stdin);

}

void editProductQty() {
    int total = 0;
    int pos;
    int oldQty;
    int newQty;
    int i;

    if(head == NULL) {
        printf("\n\n\n ------ No Product Data -----\n");

    } else {
        view();
        curr = head;

        while (curr) {
            total++;
            curr = curr -> next;
        }

        printf("\n\n");

        do {
            printf("Input Product Row [1..%d]: ", total);
            scanf("%d", &pos);
            fflush(stdin);
        } while(pos<1 || pos>total);

       curr = head;
        for (i = 1; i < pos; i++) {
            curr = curr -> next;
        }

        do {
            printf("Input New Quantity [1..50]: ");
            scanf("%d", &newQty);
            fflush(stdin);
        } while(newQty<1 || newQty>50);

        oldQty = curr -> qty;
        curr -> qty = newQty;

        printf("\n\n\nStok %s telah berganti dari %d menjadi %d\n", curr -> productName, oldQty, newQty);
    }

    getchar();
    fflush(stdin);

}

int main() {
    
    int menu;

    do {
        printf("---------------Toko Sembako Pak Andi---------------------\n");
        printf("1. Lihat Stok\n");
        printf("2. Tambah Stock\n");
        printf("3. Hapus Produk\n");
        printf("4. Edit Stok\n");
        printf("5. Keluar\n");

        printf("\nPilih menu: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1: view();
                    getchar();
                    fflush(stdin);
                    break;

            case 2: addProduct();
                    break;

            case 3: deleteProduct();
                    break;

            case 4: editProductQty();
                    break;

        }

    } while(menu != 5);

    popAll();
    
    return 0;
}