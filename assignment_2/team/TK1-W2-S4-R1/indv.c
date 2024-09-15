// Buatlah sebuah program database sederhana dengan menggunakan singly linked list!
// Program tersebut memiliki pilihan(menu) sebagai berikut:
// 1.	Push data karyawan. Ketika dijalankan, akan diminta input berupa Employee ID, Nama Lengkap, Tempat Lahir, Tanggal Lahir, dan Jabatan. Validasi Employee ID maksimal 5 angka, Nama Lengkap dan Tempat lahir maksimal 30 karakter, dan Jabatan maksimal 50 karakter. Validasi jumlah data yang dapat diinput adalah maksimal 5 data.
// 2.	Menampilkan semua daftar Karyawan di database terdiri dari Employee ID, Nama Lengkap, Tempat Tanggal Lahir, dan Jabatan. Data karyawan ditampilkan secara terurut (sort) berdasarkan Employee ID. 
// 3.	Hapus data karyawan berdasarkan Employee ID
// 4.	Hapus semua data karyawan
// 5.	Keluar dari program.
//  dalam bahasa C 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int data_count = 0;

struct data {
    char employee_id[5];
    char nama_lengkap[30]; 
    char tempat_lahir[30];
    char tanggal_lahir[11];
    char jabatan[50];

    struct data *next;
} *head, *tail, *curr;

void view() {
    printf("|---------------------------------------------------------------------------------------------------------------------------|\n");
    printf("| No. | Employee ID | Nama Lengkap                 | Tempat, Tanggal Lahir                     | Jabatan                    |\n");
    printf("|---------------------------------------------------------------------------------------------------------------------------|\n");
    int row = 0;
    curr = head;
    while (curr) {
        row++;
        printf("| %3d | %-5s | %-30s | %-30s, %-11s | %-50s | \n", row, curr -> employee_id, curr -> nama_lengkap, curr -> tempat_lahir, curr -> tanggal_lahir, curr -> jabatan);
        curr = curr -> next;
    
    }
    printf("\n\n\n\n\n");
    
}

void push(char employee_id[], char nama_lengkap[], char tempat_lahir[], char tanggal_lahir[], char jabatan[]) {

    if(data_count >= 5) {
        printf("Database mencapai jumlah maksimum 5 data\n");
        return;
    }
    
    curr = (struct data*)malloc(sizeof(struct data));
    
    strcpy(curr -> employee_id, employee_id);
    strcpy(curr -> nama_lengkap, nama_lengkap);
    strcpy(curr -> tempat_lahir, tempat_lahir);
    strcpy(curr -> tanggal_lahir, tanggal_lahir);
    strcpy(curr -> jabatan, jabatan);
    curr->next = NULL;

    if(head == NULL) {
        head = tail = curr;
    } else {
        tail->next = curr;
        tail = curr;
    }

    data_count++;
    printf("data berhasil di tambah\n");
}

void deleteById(char employee_id[]) {
    struct data *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->employee_id, employee_id) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Employee ID tidak ditemukan.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    if (temp == tail) {
        tail = prev;
    }

    free(temp);
    data_count--;
    printf("Data berhasil dihapus.\n");
}

void deleteAll() {
    struct data *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    employee_count = 0;
    printf("Semua data berhasil dihapus.\n");
}
