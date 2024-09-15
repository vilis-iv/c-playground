#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int data_count = 0;

struct data {
    char employee_id[5];
    char nama_lengkap[30]; 
    char tempat_lahir[30];
    char tanggal_lahir[10];
    char jabatan[50];

    struct data *next;
} *head, *tail, *curr;

void view() {
    if (head == NULL) {
        printf("Database Kosong.\n");
        return;
    }
    
    printf("|---------------------------------------------------------------------------------------------------------------------------|\n");
    printf("| No. | Employee ID | Nama Lengkap                 | Tempat, Tanggal Lahir                     | Jabatan                    |\n");
    printf("|---------------------------------------------------------------------------------------------------------------------------|\n");
    int row = 0;
    curr = head;
    while (curr) {
        row++;
        printf("| %3d | %-5s | %-30s | %-30s, %-10s | %-50s | \n", row, curr -> employee_id, curr -> nama_lengkap, curr -> tempat_lahir, curr -> tanggal_lahir, curr -> jabatan);
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
    
    strcpy(curr->employee_id, employee_id);
    strcpy(curr->nama_lengkap, nama_lengkap);
    strcpy(curr->tempat_lahir, tempat_lahir);
    strcpy(curr->tanggal_lahir, tanggal_lahir);
    strcpy(curr->jabatan, jabatan);
    curr->next = NULL;

    if (head == NULL) {
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
    data_count = 0;
    printf("Semua data berhasil dihapus.\n");
}

void addEmployee() {
    char employee_id[5];
    char nama_lengkap[30];
    char tempat_lahir[30];
    char tanggal_lahir[10];
    char jabatan[50];

    if (data_count >= 5) {
        printf("Database mencapai jumlah maksimum 5 data.\n");
        return;
    }

    printf("\n");

    do {
        printf("Employee ID [1..5 digit]: ");
        scanf(" %5s", employee_id);
        fflush(stdin);
    } while (strlen(employee_id) < 1 || strlen(employee_id) > 5);

    printf("\n");

    do {
        printf("Nama Lengkap [5..30 karakter]: ");
        scanf(" %[^\n]", nama_lengkap);
        fflush(stdin);
    } while (strlen(nama_lengkap) < 5 || strlen(nama_lengkap) > 30);

    printf("\n");

    do {
        printf("Tempat Lahir [5..30 karakter]: ");
        scanf(" %[^\n]", tempat_lahir);
        fflush(stdin);
    } while (strlen(tempat_lahir) < 5 || strlen(tempat_lahir) > 30);

    printf("\n");

    do {
        printf("Tanggal Lahir (YYYY-MM-DD): ");
        scanf(" %10s", tanggal_lahir);
        fflush(stdin);
    } while (strlen(tanggal_lahir) != 10);

    printf("\n");

    do {
        printf("Jabatan [5..50 karakter]: ");
        scanf(" %[^\n]", jabatan);
        fflush(stdin);
    } while (strlen(jabatan) < 5 || strlen(jabatan) > 50);

    push(employee_id, nama_lengkap, tempat_lahir, tanggal_lahir, jabatan);
    printf("Employee added.\n");
    getchar();
}

int main() {
    int menu;

    do {
        printf("---------------Employee Database-----------------\n");
        printf("1. Tampilkan Karyawan\n");
        printf("2. Tambah Karyawan\n");
        printf("3. Hapus Karyawan\n");
        printf("4. Hapus Semua Karyawan\n");
        printf("5. Keluar\n");

        printf("\nPilih Menu: ");
        scanf("%d", &menu);
        fflush(stdin);

        switch (menu) {
            case 1:
                view();
                getchar();
                break;
            case 2:
                addEmployee();
                break;
            case 3:
                if (head == NULL) {
                    printf("Database Kosong.\n");
                } else {
                    char employee_id[5];
                    printf("Masukkan Employee ID karyawan yang akan dihapus: ");
                    scanf(" %5s", employee_id);
                    fflush(stdin);
                    deleteById(employee_id);
                }
                break;
            case 4:
                deleteAll();
                break;
            case 5:
                deleteAll();
                printf("Program Keluar.\n");
                break;
            default:
                printf("Opsi tidak ditemukan.\n");
                break;
        }
    } while (menu != 5);

    return 0;
}
