#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_SIZE 100

/******************
* task struct
* *****************/
struct Task {
    int id;
    char name[50];
    int priority;
    int deadline;
    char pic[30];
};

/*******************
* min-heap struct
* ******************/
struct MinHeap {
    struct Task* tasks[HEAP_SIZE];
    int size;
};


/*********************
* initiate heap
* ********************/
struct MinHeap* initiateHeap() {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->size = 0;
    return heap;
}


/*********************
* heap swap task
* ********************/
void swap(struct Task** a, struct Task** b) {
    struct Task* temp = *a;
    *a = *b;
    *b = temp;
}


/********************
* create new task
* *******************/
struct Task* createTask(int id, char name[], int priority, int deadline, char pic[]) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    newTask->id = id;
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->deadline = deadline;
    strcpy(newTask->pic, pic);
    return newTask;
}


/*********************
* calculate deadline and priority
* ********************/
int deadline_priority_calc(struct Task* task) {
    return task->deadline + task->priority;
}


/*********************
* heapify func
* ********************/
void heapify(struct MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && deadline_priority_calc(heap->tasks[left]) < deadline_priority_calc(heap->tasks[smallest])) {
        smallest = left;
    }
    if (right < heap->size && deadline_priority_calc(heap->tasks[right]) < deadline_priority_calc(heap->tasks[smallest])) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap->tasks[i], &heap->tasks[smallest]);
        heapify(heap, smallest);
    }
}


/*********************
* insert task to heap 
* ********************/
void insertTask(struct MinHeap* heap, struct Task* task) {
    if (heap->size == HEAP_SIZE) {
        printf("Heap penuh\n");
        return;
    }

    int i = heap->size;
    heap->tasks[i] = task;
    heap->size++;

    while (i != 0 && deadline_priority_calc(heap->tasks[(i - 1) / 2]) > deadline_priority_calc(heap->tasks[i])) {
        swap(&heap->tasks[i], &heap->tasks[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    printf("Task berhasil ditambah\n");
}


/*********************
* assign task with top priority
* ********************/
struct Task* assignTask(struct MinHeap* heap) {
    if (heap->size == 0) {
        printf("Task kosong.\n");
        return NULL;
    }

    struct Task* task = heap->tasks[0];
    heap->tasks[0] = heap->tasks[--heap->size];
    heapify(heap, 0);

    printf("Informasi Task Assignment \nNama Task   : %s \nPIC         : %s\n\n", task->name, task->pic);
    return task;
}


/********************
* update task from heap
* *******************/
void updateTask(struct MinHeap* heap, int id, char name[], int priority, int deadline, char pic[]) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->tasks[i]->id == id) {
            heap->tasks[i]->priority = priority;
            heap->tasks[i]->deadline = deadline;
            strcpy(heap->tasks[i]->name, name);
            strcpy(heap->tasks[i]->pic, pic);
            
            int parent = (i - 1) / 2;
            if (i > 0 && deadline_priority_calc(heap->tasks[parent]) > deadline_priority_calc(heap->tasks[i])) {
                while (i != 0 && deadline_priority_calc(heap->tasks[(i - 1) / 2]) > deadline_priority_calc(heap->tasks[i])) {
                    swap(&heap->tasks[i], &heap->tasks[(i - 1) / 2]);
                    i = (i - 1) / 2;
                }
            } else {
                heapify(heap, i);
            }

            printf("Task berhasil di update\n");
            return;
        }
    }
    printf("Task ID: %d tidak ditemukan.\n", id);
}


/*********************
* view all tasks
* ********************/
void viewTasks(struct MinHeap* heap) {
    printf("------+----------------------------------------------------+-----+-----+---------------------------------\n");
    printf("| ID  | Task Name                                          | Pry | Dln | PIC                            |\n");
    printf("------+----------------------------------------------------+-----+-----+---------------------------------\n");
    for (int i = 0; i < heap->size; i++) {
        printf("| %3d | %-50s | %3d | %3d | %-30s |\n",
               heap->tasks[i]->id,
               heap->tasks[i]->name,
               heap->tasks[i]->priority,
               heap->tasks[i]->deadline,
               heap->tasks[i]->pic);
    }
}

int main() {
    struct MinHeap* heap = initiateHeap();
    int menu;

    do {
        printf("\n\n---------------Project Management---------------------\n");
        printf("1. Lihat Task\n");
        printf("2. Assign Task\n");
        printf("3. Insert Task\n");
        printf("4. Update Task\n");
        printf("5. Keluar\n");

        printf("\nPilih menu: ");
        scanf("%d", &menu);

        //WARN: system call code to clear terminal on unix system only.
        //Remove or comment this line if error or bug occured
        //or change "clear" to "cls"
        system("clear");

        switch (menu) {
            case 1: viewTasks(heap);
                    break;

            case 2: assignTask(heap);
                    break;

            case 3: { 
                        int id;
                        char name[50];
                        int priority;
                        int deadline;
                        char pic[30];

                        printf("Id Task     : ");
                        scanf("%d", &id);

                        printf("Nama Task   : ");
                        scanf(" %[^\n]", name);

                        printf("Prioritas   : ");
                        scanf("%d", &priority);


                        printf("Deadline    : ");
                        scanf("%d", &deadline);

                        printf("PIC         : ");
                        scanf(" %[^\n]", pic);

                        insertTask(heap, createTask(id, name, priority, deadline, pic));
                    }
                    break;

            case 4: {
                        int id;
                        char name[50];
                        int priority;
                        int deadline;
                        char pic[30];

                        printf("Id Task     : ");
                        scanf("%d", &id);

                        printf("Nama Task   : ");
                        scanf(" %[^\n]", name);

                        printf("Prioritas   : ");
                        scanf("%d", &priority);


                        printf("Deadline    : ");
                        scanf("%d", &deadline);

                        printf("PIC         : ");
                        scanf(" %[^\n]", pic);

                        updateTask(heap, id, name, priority, deadline, pic);
                    
                    }
                    break;

        }

    } while(menu != 5);

    return 0;
}
