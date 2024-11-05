#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
	int data;
    struct node *next;
};
typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head, int key);
void hapusAkhir(node **head);
void tranverse(node *head);
int cariData(node *head, int key);
int hitungJumlahNode(node *head);
int totalData(node *head);

//========================================================

int main()
{
  node *head;
  char pilih;
  int key;

  head = NULL;
  do{
     system("cls");
     printf("masukkan pilihan\n");
     printf("1. tambah data di awal\n");
     printf("2. tambah data di tengah list\n");
     printf("3. tambah data di akhir list\n");
     printf("4. hapus data di awal\n");
     printf("5. hapus data di tengah\n");
     printf("6. hapus data di akhir\n");
     printf("7. cari data\n");
     printf("8. cetak isi list\n");
     printf("9. jumlah node dalam list\n");
     printf("masukkan t untuk menjumlahkan data dalam list\n");
     printf("MASUKKAN PILIHAN (masukkan q untuk keluar) : ");
     fflush(stdin);
     scanf("%c", &pilih);

     if (pilih == '1')
     	tambahAwal(&head);
     else if (pilih == '2')
		tambahData(&head);
	 else if (pilih == '3')
	 	tambahAkhir(&head);
	 else if (pilih == '4')
	 	hapusAwal(&head);
	 else if (pilih == '5') {
        printf("Masukkan nilai yang ingin dihapus: ");
        scanf("%d", &key);
        hapusTengah(&head, key);
     }
     else if (pilih == '6')
        hapusAkhir(&head);
     else if (pilih == '7') {
        printf("Masukkan data yang dicari: ");
        scanf("%d", &key);
        if (cariData(head, key))
            printf("Data ditemukan!\n");
        else
            printf("Data tidak ditemukan.\n");
        getch();
     }
     else if (pilih == '8') {
     	tranverse(head);
         getch();
     }
     else if (pilih == '9'){
        printf("Jumlah node dalam list: %d\n", hitungJumlahNode(head));
        getch();
     }
     else if (pilih == 't'){
        printf("Total penjumlahan data dalam list: %d\n", totalData(head));
        getch();
     }
  } while (pilih != 'q');
  
  return 0;
}

//========================================================

void tambahAwal(node **head){
  int bil;
  node *pNew, *pCur;

  system("cls");
  fflush(stdin);
  printf("masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      if (*head == NULL) {
        pNew->next = pNew; // Point to itself if it's the first node
        *head = pNew;
      } else {
        pCur = *head;
        while (pCur->next != *head) { // Find the last node
          pCur = pCur->next;
        }
        pNew->next = *head; // Point new node to head
        pCur->next = pNew;  // Update last node to point to the new node
        *head = pNew; // Update head to point to the new node
      }
      printf("data berhasil ditambahkan!");
      getch();
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahData(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pCur = *head;
  do {
    if (pCur->data == pos) {
      break;
    }
    pCur = pCur->next;
  } while (pCur != *head);

  if (pCur->data != pos) {
    printf("\nnode tidak ditemukan");
    getch();
    return;
  }

  pNew = (node *)malloc(sizeof(node));
  if (pNew == NULL){
     printf("\nalokasi memori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = pCur->next;
     pCur->next = pNew;
     printf("data berhasil ditambahkan!");
     getch();
  }
}

//========================================================
void tambahAkhir(node **head) {
  int bil;
  node *pNew, *pCur;

  system("cls");
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pNew = (node *)malloc(sizeof(node));

  if (pNew == NULL){
     printf("\nalokasi memori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     if (*head == NULL) {
        pNew->next = pNew;
        *head = pNew;
     } else {
        pCur = *head;
        while (pCur->next != *head) {
          pCur = pCur->next;
        }
        pCur->next = pNew;
        pNew->next = *head;
     }
    printf("data berhasil ditambahkan!");
    getch();
  }
}

//========================================================

void hapusAwal(node **head) {
  node *pCur;

  if (*head == NULL) {
    printf("List kosong!\n");
    getch();
    return;
  }

  if (*head == (*head)->next) {
    free(*head);
    *head = NULL;
  } else {
    pCur = *head;
    while (pCur->next != *head) {
      pCur = pCur->next;
    }
    node *pDel = *head;
    pCur->next = (*head)->next;
    *head = (*head)->next;
    free(pDel);
  }
  printf("data berhasil dihapus!");
  getch();
}

//========================================================

void hapusTengah(node **head, int key) {
  node *pCur, *pPrev;

  if (*head == NULL) {
    printf("List kosong!\n");
    getch();
    return;
  }

  pCur = *head;
  do {
    if (pCur->data == key) {
      break;
    }
    pPrev = pCur;
    pCur = pCur->next;
  } while (pCur != *head);

  if (pCur->data != key) {
    printf("Data tidak ditemukan!\n");
    getch();
    return;
  }

  if (pCur == *head && pCur->next == *head) {
    *head = NULL;
  } else if (pCur == *head) {
    pPrev = *head;
    while (pPrev->next != *head) {
      pPrev = pPrev->next;
    }
    pPrev->next = (*head)->next;
    *head = (*head)->next;
  } else {
    pPrev->next = pCur->next;
  }

  free(pCur);
  printf("data berhasil dihapus!");
  getch();
}

//========================================================

void hapusAkhir(node **head) {
  node *pCur, *pPrev;

  if (*head == NULL) {
    printf("List kosong!\n");
    getch();
    return;
  }

  pCur = *head;
  if (pCur->next == *head) {
    free(*head);
    *head = NULL;
  } else {
    while (pCur->next != *head) {
      pPrev = pCur;
      pCur = pCur->next;
    }
    pPrev->next = *head;
    free(pCur);
  }
  printf("data berhasil dihapus!");
  getch();
}

//========================================================

int cariData(node *head, int key) {
  node *pCur = head;
  if (head == NULL) return 0;

  do {
    if (pCur->data == key)
      return 1; // Data ditemukan
    pCur = pCur->next;
  } while (pCur != head);
  
  return 0;
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    if (head == NULL) {
        printf("List kosong!\n");
        return;
    }

    pWalker = head;
    do {
        printf("%d", pWalker->data);
        pWalker = pWalker->next;
        if (pWalker != head) printf(" -> ");
    } while (pWalker != head);
    printf(" -> kembali ke awal (%d)\n", head->data);
}

//========================================================

int hitungJumlahNode(node *head) {
    int count = 0;
    node *pWalker;

    if (head == NULL) {
        return 0;
    }

    pWalker = head;
    do {
        count++;
        pWalker = pWalker->next;
    } while (pWalker != head);

    return count;
}

//========================================================

int totalData(node *head) {
    int sum = 0;
    node *pWalker;

    if (head == NULL) {
        return 0;
    }

    pWalker = head;
    do {
        sum += pWalker->data;
        pWalker = pWalker->next;
    } while (pWalker != head);

    return sum;
}

