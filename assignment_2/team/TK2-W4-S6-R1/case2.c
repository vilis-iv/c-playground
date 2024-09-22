#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct konsumen {
    char nama[20];
    char pesanan[20];
    int qty;
    struct konsumen *next;
} *front, *rear, *curr;

void view() {
    if (front == NULL) {
        printf("---------------------Antrian kosong!-----------------------\n");
        return;
    }

    int row = 0;
    curr = front;
    
    printf("|-----+----------------------+----------------------+-----|\n");
    printf("| No. | Nama Konsumen        | Pesanan              | Qty |\n");
    printf("|-----+----------------------+----------------------+-----|\n");

    while (curr) {
        row++;
        printf("| %3d | %-20s | %-20s | %3d |\n", row, curr->nama, curr->pesanan, curr->qty);
        curr = curr->next;
    }

    printf("|-----+----------------------+----------------------+-----|\n\n");
}

void enqueue(char name[], char pesanan[], int qty) {
    curr = (struct konsumen*)malloc(sizeof(struct konsumen));

    strcpy(curr->nama, name);
    strcpy(curr->pesanan, pesanan);
    curr->qty = qty;

    if(front == NULL) {
        front = rear = curr;
    } else {
        rear->next = curr;
        curr->next = NULL;
        rear = curr;
    }
}

void dequeue() {
    if(front != NULL) {
        struct konsumen *temp = front;

        if(front == rear) {
            front = rear = NULL;
        } else {
            front = front->next;
        }

        free(temp);
    }
}

int main() {

    /*************************************
     * Simulasi Konsumen Masuk Antrian
     *************************************/
    enqueue("Pramudia", "Ayam Bakar", 2);
    enqueue("Putra", "Sate", 3);
    enqueue("Pamungkas", "Soda", 4);


    /*************************************
     * Simulasi Konsumen Keluar Antrian
     *************************************/
    view();
    dequeue();  //Konsumen pertama

    view();
    dequeue();  //Konsumen kedua
    
    view();
    dequeue();  //Konsumen ketiga

    view();

}