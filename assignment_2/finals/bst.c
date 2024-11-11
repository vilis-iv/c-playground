#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********************
* Product struct
* *******************/
struct Product {
    int     id;
    char    name[50];
    float   price;
    int     sold_count;
};

/*********************
* Node struct for BST
* ********************/
struct Node {
    struct Product product;
    struct Node* left;
    struct Node* right;
} Node;



/**********************
* create new node
* *********************/
struct Node* createNode(int id, char name[], float price) {
    struct Node* newNode = (struct Node*)malloc(sizeof(Node));
    newNode->product.id = id;
    strcpy(newNode->product.name, name);
    newNode->product.price = price;
    newNode->product.sold_count = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/**********************
* add product into BST
* *********************/
struct Node* addProduct(struct Node* root, int id, char name[], float price) {
    if (root == NULL) {
        return createNode(id, name, price);
    }

    if (id < root->product.id) {
        root->left = addProduct(root->left, id, name, price);
    } else if (id > root->product.id) {
        root->right = addProduct(root->right, id, name, price);
    } else {
        printf("Produk dengan ID %d sudah ada, silakan masukkan ID baru.\n", id);
    }

    return root;
}


/**********************
* Search product by ID
* *********************/
struct Node* searchProduct(struct Node* root, int id) {
    if (root == NULL || root->product.id == id) {
        return root;
    }

    if (id < root->product.id) {
        return searchProduct(root->left, id);
    } else {
        return searchProduct(root->right, id);
    }
}


/**********************
* Delete product by ID
* *********************/
struct Node* deleteProduct(struct Node* root, int id) {
    if (root == NULL) return root;

    if (id < root->product.id) {
        root->left = deleteProduct(root->left, id);
    } else if (id > root->product.id) {
        root->right = deleteProduct(root->right, id);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->product = temp->product;
        root->right = deleteProduct(root->right, temp->product.id);
    }

    return root;
}


/*****************************
* update product sold counter
* ****************************/
void sellProduct(struct Node* root, int id, int sold_count) {
    struct Node* node = searchProduct(root, id);
    if (node != NULL) {
        node->product.sold_count += sold_count;
        printf("%s sebanyak %d berhasil dijual.\n", node->product.name, sold_count);
    } else {
        printf("Produk dengan ID %d tidak ditemukan.\n", id);
    }
}


/*************************
* view product details
* ************************/
void viewProduct(struct Node* root) {

    if (root != NULL) {
        viewProduct(root->left);
        
        printf("| %3d | %-50s | %15.2f | %4d |\n",
               root->product.id, 
               root->product.name,
               root->product.price, 
               root->product.sold_count);
        
        viewProduct(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int menu;

    do {
        printf("\n\n---------------Menu Toko Elektronik---------------------\n");
        printf("1. Lihat Produk\n");
        printf("2. Jual Produk\n");
        printf("3. Tambah Produk\n");
        printf("4. Hapus Produk\n");
        printf("5. Keluar\n");

        printf("\nPilih menu: ");
        scanf("%d", &menu);

        //WARN: system call code to clear terminal on unix system only.
        //Remove or comment this line if error or bug occured
        //or change "clear" to "cls"
        system("clear");

        switch (menu) {
            case 1:{
                        printf("------+----------------------------------------------------+-----------------+-------\n");
                        printf("| ID  | Product Name                                       |           Price | Sold |\n");
                        printf("------+----------------------------------------------------+-----------------+-------\n");
                        viewProduct(root);
                    }      
                    break;

            case 2: {
                        int id;
                        int sold_count;
                    
                        printf("Id Produk: ");
                        scanf("%d", &id);

                        printf("Jumlah: ");
                        scanf("%d", &sold_count);
                        sellProduct(root, id, sold_count);
                    }
                    break;

            case 3: { 
                        int id;
                        char name[50];
                        float price;
                    
                        printf("Id Produk: ");
                        scanf("%d", &id);

                        printf("Nama Produk: ");
                        scanf(" %[^\n]", name);

                        printf("Harga Produk: ");
                        scanf("%f", &price);
                        root = addProduct(root, id, name, price);
                    }
                    break;

            case 4: {
                        int id;
                    
                        printf("Id Produk: ");
                        scanf("%d", &id);
                        deleteProduct(root, id);
                    
                    }
                    break;

        }

    } while(menu != 5);

    return 0;
}