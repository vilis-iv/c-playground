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

struct data {
    char employee_id[5];
    char nama_lengkap[30]; 
    char tempat_lahir[30];
    char tanggal_lahir[11];
    char jabatan[50];

    struct data *next;
} *head, *tail, *curr;

void view() {
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
    curr = (struct data*)malloc(sizeof(struct data));
    
    strcpy(curr -> employee_id, employee_id);
    strcpy(curr -> nama_lengkap, nama_lengkap);
    strcpy(curr -> tempat_lahir, tempat_lahir);
    strcpy(curr -> tanggal_lahir, tanggal_lahir);
    strcpy(curr -> jabatan, jabatan);
}
