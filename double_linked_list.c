#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
	int data;
    struct node *next;
    struct node *prev; // Add a previous pointer
};
typedef struct node node;

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
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = *head;
      pNew->prev = NULL;
	  
      if (*head != NULL) {
          (*head)->prev = pNew;
      }
      *head = pNew;
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
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nnode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nalokasi memori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = pCur->next;
     pNew->prev = pCur;
     
     if (pCur->next != NULL) {
         pCur->next->prev = pNew;
     }
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
     pNew->next = NULL;
     if (*head == NULL) {
        pNew->prev = NULL;
        *head = pNew;
     } else {
        pCur = *head;
        while (pCur->next != NULL) {
          pCur = pCur->next;
        }
        pCur->next = pNew;
        pNew->prev = pCur;
     }
    printf("data berhasil ditambahkan!");
    getch();
  }
}

//========================================================

void hapusAwal(node **head) {
  node *pDel;

  if (*head != NULL) {
    pDel = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(pDel);
    printf("data berhasil dihapus!");
    getch();
  } else {
    printf("List kosong!\n");
    getch();
  }
}

//========================================================

void hapusTengah(node **head, int key) {
  node *pCur;

  pCur = *head;

  while (pCur != NULL && pCur->data != key) {
    pCur = pCur->next;
  }

  if (pCur == NULL) {
    printf("Data tidak ditemukan!\n");
    getch();
  } else {
    if (pCur->prev != NULL) {
      pCur->prev->next = pCur->next;
    } else {
      *head = pCur->next;
    }
    
    if (pCur->next != NULL) {
      pCur->next->prev = pCur->prev;
    }
    free(pCur);
    printf("data berhasil dihapus!");
    getch();
  }
}

//========================================================

void hapusAkhir(node **head) {
  node *pCur;

  if (*head == NULL) {
    printf("List kosong!\n");
    getch();
    return;
  }

  pCur = *head;

  while (pCur->next != NULL) {
    pCur = pCur->next;
  }

  if (pCur->prev != NULL) {
    pCur->prev->next = NULL;
  } else {
    *head = NULL;
  }

  free(pCur);
  printf("data berhasil dihapus!");
  getch();
}

//========================================================

int cariData(node *head, int key) {
  node *pCur = head;
  while (pCur != NULL) {
    if (pCur->data == key)
      return 1; // Data ditemukan
    pCur = pCur->next;
  }
  return 0; // Data tidak ditemukan
}

//========================================================

int hitungJumlahNode(node *head) {
  int count = 0;
  node *pCur = head;
  while (pCur != NULL) {
    count++;
    pCur = pCur->next;
  }
  return count;
}

//========================================================

int totalData(node *head) {
  int sum = 0;
  node *pCur = head;
  while (pCur != NULL) {
    sum += pCur->data;
    pCur = pCur->next;
  }
  return sum;
}

//========================================================

void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

   system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d", pWalker -> data);
   	pWalker = pWalker -> next;
    if (pWalker != NULL) printf(" <-> ");
	} 
   printf(" <-> NULL\n");
}

