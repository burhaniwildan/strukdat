#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define LIMIT 20


struct Node {
    char data[MAX];
    struct Node* next;
};


struct Node* createNode(char *data) {
	system("cls");
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (!newNode) {
        printf("alokasi memori gagal.\n");
        exit(1);
    }
    strcpy(newNode->data, data);
    newNode->next = newNode;  
    return newNode;
}


void addNode(struct Node** tail, char *data, int *count) {
	if (*count >= LIMIT) {
        printf("list penuh");
        return;
    }
	
    struct Node* newNode = createNode(data);
    
    if (*tail == NULL) {
        *tail = newNode;
        (*tail)->next = *tail;
    } else {
        newNode->next = (*tail)->next;
        (*tail)->next = newNode;
        *tail = newNode;
    }
}


void deleteNode(struct Node** tail, char *data, int *count) {
    if (*tail == NULL) {
        printf("List kosong.\n");
        return;
    }
    
    struct Node *temp = (*tail)->next, *prev = *tail;
    do {
        if (strcmp(temp->data, data) == 0) {
            if (temp == *tail && temp->next == *tail) {
                *tail = NULL;  
            } else {
                if (temp == *tail) {
                    *tail = prev;
                }
                prev->next = temp->next;
            }
            free(temp);
            (*count)--;
            printf("Data '%s' berhasil dihapus.\n", data);
            getch();
            return;
        }
        prev = temp;
        temp = temp->next;
    } while (temp != (*tail)->next);
    
    printf("Data '%s' tidak ditemukan.\n", data);
    getch();
}


void display(struct Node* tail) {
    if (tail == NULL) {
        printf("List kosong.\n");
        return;
    }
    
    struct Node* temp = tail->next;
    do {
        printf("%s -> ", temp->data);
        temp = temp->next;
    } while (temp != tail->next);
    printf("(kembali ke awal)\n");
    getch();
}

int main() {
    struct Node* tail = NULL;
    int pilihan;
    char input[MAX];
    int count = 0;
    
    do {
    	system("cls");
        printf("\nMenu:\n");
        printf("1. Tambah data\n");
        printf("2. Hapus data\n");
        printf("3. Tampilkan list\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);
        getchar(); 
        
        switch (pilihan) {
            case 1:
            	system("cls");
                printf("Masukkan nama mahasiswa: ");
                fgets(input, MAX, stdin);
                input[strcspn(input, "\n")] = '\0'; 
                addNode(&tail, input, &count);
                break;
                
            case 2:
            	system("cls");
            	display(tail);
                printf("Masukkan nama mahasiswa yang ingin dihapus: ");
                fgets(input, MAX, stdin);
                input[strcspn(input, "\n")] = '\0';
                deleteNode(&tail, input, &count);
                break;
                
            case 3:
            	system("cls");
                display(tail);
                break;
                
            case 4:
                printf("Keluar dari program.\n");
                break;
                
            default:
                printf("Pilihan tidak valid.\n");
                getch();
                break;
        }
    } while (pilihan != 4);
    
    return 0;
}

