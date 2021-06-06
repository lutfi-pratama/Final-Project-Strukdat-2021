#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LIMIT 50
#define MIN_LIMIT 50

// Data Pelanggan ===================================
struct pelanggan
{
    int kode;
    char barang[MAX_LIMIT][MAX_LIMIT];
    int jumlah[MAX_LIMIT];
    long long int total;
    char status[MAX_LIMIT];
    struct pelanggan *next;
};
typedef struct pelanggan pelanggan;

// Data Barang Jual =================================
struct barangJual
{
    struct barangJual *prev;
    char namaBarJul[MAX_LIMIT];
    int stok;
    long long int harga;
    struct barangJual *next;
};
typedef struct barangJual barangJual;

// Data Barang Gudang (Queue) ================================
struct barang
{
    char namaBarang[MAX_LIMIT];
    int expBulanBarang;
    int expTahunBarang;
    int stokBarang;
    struct barang *next;
};
typedef struct barang barang;

struct queue
{
    int count;
    barang *front;
    barang *rear;
};
typedef struct queue queue;

// Data Doorprize =============================================
struct prize
{
    int kodePrize;
    char namaPrize[MAX_LIMIT];
    struct prize *next;
};
typedef struct prize prize;

struct stack
{
    int countPrize;
    prize *top;
};
typedef struct stack stack;

//Pelanggan
void insertP(pelanggan **head, barangJual **head2, stack *head3);

//Barang Jual
void addBarangJual(barangJual **head2, queue *myQueue);
void decreaseStok(barangJual **head2, char barang[][MAX_LIMIT], int jumlah[], int i);
void catatHarga(barangJual **head2, char barang[][MAX_LIMIT], long long int *total, int i, int jumlah[]);
void popBarangJual(barangJual **head2); // not use

//Doorprize (stack)
stack createStack(void);
int isFull(stack *head3);
int isEmpty(stack *head3);
void addPrize(stack *head3);
void popPrize(stack *head3, long long int total);
void showPrize(stack *head3);

// Additional
void insertNode(pelanggan **head, pelanggan *pPre, pelanggan *pNew);
void tranverse(pelanggan *head);
void tranverseBarJul(barangJual *head2);
void deleteList(pelanggan *head, barangJual *head2, stack *head3, queue *myQueue);

// Barang Jual (Queue)
queue createQueue(void)
{
    queue myQueue;

    myQueue.count = 0;
    myQueue.front = NULL;
    myQueue.rear = NULL;
    return (myQueue);
}

int checkEmpty(queue *myQueue)
{
    if (myQueue->front == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void tranverseBarangGudang(queue myQueue)
{
    system("cls");

    barang *temp;

    temp = myQueue.front;
    printf("List barang dari front (siap ambil) ke rear (ambil akhir):\n");
    printf("_____________________________________________________________\n");
    while (temp)
    {
        printf("%s (exp: %d, %d)\t(stok: %d)\n", temp->namaBarang, temp->expBulanBarang, temp->expTahunBarang, temp->stokBarang);
        temp = temp->next;
    }
}

void enqueueBarangGudang(queue *myQueue)
{
    system("cls");

    if (myQueue->count >= 20)
    {
        printf("\n_______ Stok Gudang Penuh _______\n");
        printf("\n");
    }
    else
    {
        int bulanExpired, tahunExpired, stokBarang;
        char namaBarang[MAX_LIMIT];

        barang *temp;
        temp = (barang *)malloc(sizeof(barang));

        fflush(stdin);
        printf("Masukkan nama barang : ");
        fflush(stdin);
        scanf("%[^\n]%*c", namaBarang);
        fflush(stdin);
        printf("Bulan expired barang : ");
        fflush(stdin);
        scanf("%d", &bulanExpired);
        fflush(stdin);
        printf("Tahun expired barang : ");
        fflush(stdin);
        scanf("%d", &tahunExpired);
        fflush(stdin);
        printf("Stok barang : ");
        fflush(stdin);
        scanf("%d", &stokBarang);
        fflush(stdin);

        strcpy(temp->namaBarang, namaBarang);
        temp->expBulanBarang = bulanExpired;
        temp->expTahunBarang = tahunExpired;
        temp->stokBarang = stokBarang;
        temp->next = NULL;

        if (checkEmpty(myQueue))
        {
            myQueue->front = temp;
        }
        else
        {
            myQueue->rear->next = temp;
        }

        myQueue->rear = temp;
        myQueue->count++;

        printf("\nenqueue berhasil\n");
    }
}

void dequeueBarangGudang(queue *myQueue)
{
    char namaBarang[MAX_LIMIT];

    if (myQueue->count == 0)
    {
        printf("\nQueue is empty (Barang gudang sedang kosong)\n");
    }
    else
    {
        

        barang *delNodeBarang;
        delNodeBarang = myQueue->front;
        strcpy(namaBarang, delNodeBarang->namaBarang);
        myQueue->front = myQueue->front->next;
        free(delNodeBarang);
        myQueue->count--;

        printf("Barang --%s--, telah dipindahkan dari gudang\n\n", namaBarang);
        printf("\n___________________________________________________\n");
    }
}

// =====================================================  Main

int main()
{
    // pelanggan
    pelanggan *head;
    head = NULL;
    // barang di toko / barang jual
    barangJual *head2;
    head2 = NULL;
    // stack doorprize
    stack head3;
    head3 = createStack();
    // queue barang gudang
    queue myQueue;
    myQueue = createQueue();

    int choice, choice2, success;

    while (1)
    {
        system("cls");
        printf("\n\t Program Mini Market \n");
        printf("\n====================================\n");
        printf("\n1. Penjualan");         // almost clear
        printf("\n2. Riwayat Penjualan"); // almost clear
        printf("\n3. Kelola Barang");     // on progres
        printf("\n0. Exit");
        printf("\n\nMasukkan pilihan Anda: ");
        scanf("%d", &choice);
        printf("\n\n");

        switch (choice)
        {
        case 1:
            insertP(&head, &head2, &head3);
            break;
        case 2:
            tranverse(head);
            getch();
            break;
        case 3:
            system("cls");
            printf("\n\t\t Kelola Barang \n");
            printf("\n__________________________________________________\n");
            printf("\n1. Lihat stok barang jual di Market");    // almost clear
            printf("\n2. Tambah stok barang jual di Market\n"); // almost clear
            printf("\n3. Lihat stok doorprize");                // clear
            printf("\n4. Tambah stok doorprize\n");             // clear
            printf("\n5. Lihat stok barang jual di Gudang");    // on progres
            printf("\n6. Tambah stok barang di Gudang\n");      // on progres
            printf("\n0. Kembali");                             // on progres
            printf("\n\nMasukkan pilihan Anda: ");
            scanf("%d", &choice2);
            printf("\n\n");

            switch (choice2)
            {
            case 1:
                tranverseBarJul(head2);
                getch();
                break;
            case 2:
                addBarangJual(&head2, &myQueue);
                getch();
                break;
            case 3:
                showPrize(&head3);
                getch();
                break;
            case 4:
                addPrize(&head3);
                getch();
                break;
            case 0:
                break;
            default:
                break;
            }

            break;
        case 4:
            enqueueBarangGudang(&myQueue);
            // popBarangJual(&head2);
            getch();
            break;
        case 5:
            tranverseBarangGudang(myQueue);
            getch();
            break;

        case 0:
            deleteList(head, head2, &head3, &myQueue);
            return 0;
            break;

        default:
            break;
        }
    }

    return 0;
}

// =====================================================  Function

void insertNode(pelanggan **head, pelanggan *pPre, pelanggan *pNew)
{
    if (pPre == NULL)
    {
        //menambahkan diawal atau pada empty list
        pNew->next = *head;
        *head = pNew;
    }
    else
    {
        //menambahkan node di tengah atau di akhir
        pNew->next = pPre->next;
        pPre->next = pNew;
    }
}

void tranverse(pelanggan *head)
{
    system("cls");

    // Date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("==================================================\n");
    printf("\t\tLaporan Penjualan\n");
    printf("==================================================\n");
    printf("Tanggal: %02d-%02d-%d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    //traverse linked list
    pelanggan *pWalker;
    int i = 0;

    pWalker = head;

    printf("%-14s | %3s | %3s | %3s\n\n", "Barang Terjual", "Jumlah", "Total Harga", "Status");
    while (pWalker != NULL)
    {
        for (int i = 0; pWalker->jumlah[i] != 0; i++)
        {
            if (strcmp(pWalker->barang[i], "invalid") == 0)
            {
                continue;
            }
            else
            {
                printf("%-14s | %d\n", pWalker->barang[i], pWalker->jumlah[i]);
            }
        }

        printf("%-14s   %3s  | %lld\t| %3s\n", "              ", "     ", pWalker->total, pWalker->status);

        printf("\n");
        pWalker = pWalker->next;
    }

    printf("\n");
}

void tranverseBarJul(barangJual *head2)
{
    system("cls");

    barangJual *pWalker;

    pWalker = head2;
    while (pWalker != NULL)
    {
        printf("%s\n", pWalker->namaBarJul);
        printf("%d\n\n", pWalker->stok);
        pWalker = pWalker->next;
    }
}

void insertbarang(pelanggan **head, pelanggan *pPre, pelanggan *pNew)
{
    if (pPre == NULL)
    {
        //menambahkan diawal atau pada empty list
        pNew->next = *head;
        *head = pNew;
    }
    else
    {
        //menambahkan barang di tengah atau di akhir
        pNew->next = pPre->next;
        pPre->next = pNew;
    }
}

void insertP(pelanggan **head, barangJual **head2, stack *head3)
{
    system("cls");

    char barang[MAX_LIMIT][MAX_LIMIT], choice;
    int jumlah[MAX_LIMIT], i, sum;
    i = 0;
    sum = 1;
    long long int total;
    total = 0;

    pelanggan *temp, *cur;
    temp = (pelanggan *)malloc(sizeof(pelanggan));

    if (temp == NULL)
    {
        printf("Alokasi memori gagal");
        getch();
    }
    else
    {
        while (1)
        {
            fflush(stdin);
            printf("Nama barang : ");
            fflush(stdin);
            scanf("%s", &barang[i][0]);
            fflush(stdin);
            printf("Jumlah : ");
            fflush(stdin);
            scanf("%d", &jumlah[i]);
            fflush(stdin);

            decreaseStok(head2, barang, jumlah, i);       // kurangi stok
            catatHarga(head2, barang, &total, i, jumlah); // pencatatan total harga tiap pelanggan

            i++;
            printf("\nTambah barang ? [y/n] ");
            fflush(stdin);
            scanf("%c", &choice);
            fflush(stdin);
            if (choice == 'n')
                break;

            sum++;
        }

        cur = *head;

        if (cur != NULL)
        {
            while (cur->next != NULL)
            {
                cur = cur->next;
            }
        }

        // Insert input data pelanggan ke node temp linked list Pelanggan
        // Terima Doorprize
        if (total > 50000 && head3->countPrize > 0)
        {
            if (head3->countPrize == 0)
            {
                strcpy(temp->status, "Doorprize habis");
            }
            else
            {
                strcpy(temp->status, "penerima doorprize");

                popPrize(head3, total);
            }
        }
        else
        {
            strcpy(temp->status, "-");
        }
        // catat barang yang dibeli
        for (int i = 0; i < sum; i++) // n barang relatif
        {
            strcpy(temp->barang[i], barang[i]);
            temp->jumlah[i] = jumlah[i];
        }
        getch();
        temp->total = total;
        temp->next = NULL;
        insertNode(head, cur, temp);
    }
}

void addBarangJual(barangJual **head2, queue *myQueue)
{
    system("cls");

    if (myQueue->count == 0)
    {
        printf("\nTambahkan dahulu stok di Gudang\n");
        printf("_________________________________\n\n");
        return;
    }

    int n_stok, bulanExpired, tahunExpired;
    long long int harga;

    barangJual *temp, *pNew;
    barang *tempQueue;
    tempQueue = myQueue->front;

    fflush(stdin);
    printf("Tentukan batas expired barang untuk dijual \n");
    printf("___________________________________________\n");
    fflush(stdin);
    printf("Bulan : ");
    fflush(stdin);
    scanf("%d", &bulanExpired);
    fflush(stdin);
    printf("Tahun : ");
    fflush(stdin);
    scanf("%d", &tahunExpired);
    fflush(stdin);

    while (tempQueue)
    {
        if (tempQueue->expTahunBarang <= tahunExpired)
        {
            // tambah deque berdasarkan expired 
            if (tempQueue->expBulanBarang <= bulanExpired || tempQueue->expTahunBarang < tahunExpired)
            { // cek dibawah bulan dan tahun yang ditentukan
                //Inti code add barang

                fflush(stdin);
                printf("\n%s, (stok: %d) --- Berhasil ditambahkan ke Market\n\n ", tempQueue->namaBarang, tempQueue->stokBarang);
                printf("Tentukan harga per-satuan barang : ");
                fflush(stdin);
                scanf("%lld", &harga);
                fflush(stdin);

                if ((*head2) == NULL) // menambah saat stok di market kosong
                {
                    temp = (barangJual *)malloc(sizeof(barangJual));

                    if (temp != NULL)
                    {
                        temp->prev = NULL;
                        strcpy(temp->namaBarJul, tempQueue->namaBarang);
                        temp->stok = tempQueue->stokBarang;
                        temp->harga = harga;
                        temp->next = NULL;
                        (*head2) = temp;

                        printf("\n--- Berhasil ditambahkan ---\n\n");
                    }
                    else
                    {
                        printf("Alokasi memori gagal");
                    }
                }
                else // menambah waktu stok di market ada
                {
                    temp = (*head2);

                    pNew = (barangJual *)malloc(sizeof(barangJual));

                    pNew->prev = NULL;
                    strcpy(pNew->namaBarJul, tempQueue->namaBarang);
                    pNew->stok = tempQueue->stokBarang;
                    pNew->harga = harga;
                    pNew->next = NULL;

                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }

                    if (pNew != NULL)
                    {
                        temp->next = pNew;
                        pNew->prev = temp;

                        printf("\n--- Berhasil ditambahkan ---\n\n");
                    }
                    else
                    {
                        printf("Alokasi memori gagal");
                    }
                }

                dequeueBarangGudang(myQueue);

            }
            else
                break;

            if (tempQueue->next != NULL)
            {
                if (tempQueue->next->expTahunBarang > tahunExpired) // saat next tahun exp gudang lebih dari exp inputs
                    break;
            }
        }

        if (tempQueue->expTahunBarang > tahunExpired)
        { // cek ketika masukan expired tidak dengan stok barang Gudang
            printf("\nStok barang dibawah expired tersebut tidak tersedia di Gudang Barang\n");
            break;
        }
        tempQueue = tempQueue->next;
    }
}

void decreaseStok(barangJual **head2, char barang[][MAX_LIMIT], int jumlah[], int i)
{
    int cond;
    barangJual *temp;
    temp = (*head2);

    if (temp == NULL)
    {
        // kondisi stok market kosong
        printf("Barang di Minimarket kosong, silahkan cek persediaan gudang\n");
        strcpy(barang[i], "invalid");
    }
    else
    {
        while (temp != NULL)
        {
            cond = strcmp(temp->namaBarJul, barang[i]);
            if (cond == 0)
            {
                // mengurangi stok Barang Jual
                if ((temp->stok - jumlah[i]) < 0)
                {
                    // kondisi barang kosong
                    printf("Barang sedang kosong atau stok barang tidak mencukupi permintaan\n");
                    strcpy(barang[i], "invalid");
                }
                else
                {
                    temp->stok -= jumlah[i];
                }
                break;
            }

            if (temp->next == NULL) // kondisi barang tidak tersedia
            {
                printf("Barang tidak tersedia di Minimarket\n");
                strcpy(barang[i], "invalid");
            }
            temp = temp->next;
        }
    }
}

void catatHarga(barangJual **head2, char barang[][MAX_LIMIT], long long int *total, int i, int jumlah[])
{
    int cond;
    barangJual *temp;
    temp = (*head2);

    if (temp == NULL)
    {
        return;
    }
    else
    {
        while (temp != NULL)
        {
            cond = strcmp(temp->namaBarJul, barang[i]);
            if (cond == 0)
            {
                // Totalan
                *total += (temp->harga * jumlah[i]);
                break;
            }

            temp = temp->next;
        }
    }
}

void popBarangJual(barangJual **head2)
{
    barangJual *temp;
    temp = (*head2);

    printf("cek");
    *head2 = (*head2)->next;
    free(temp);
}

stack createStack(void)
{
    stack head;
    head.countPrize = 0;
    head.top = NULL;
    return (head);
}

int isFull(stack *head3)
{
    int cond;

    if (head3->countPrize == 2) // batas stok doorprize perhari rata2 10 barang
    {
        cond = 1;
    }
    else
    {
        cond = 0;
    }

    return cond;
}

int isEmpty(stack *head3)
{
    int cond;
    if (head3->countPrize == 0)
    {
        cond = 1;
    }
    else
    {
        cond = 0;
    }
    return cond;
}

void addPrize(stack *head3)
{
    system("cls");

    int success;
    success = isFull(head3);

    if (success == 0)
    {
        int kodeD;
        char namaD[MAX_LIMIT];
        prize *baru;
        baru = (prize *)malloc(sizeof(prize));

        fflush(stdin);
        printf("Kode barang doorprize : ");
        fflush(stdin);
        scanf("%d", &kodeD);
        fflush(stdin);
        printf("Nama barang doorprize : ");
        fflush(stdin);
        scanf("%[^\n]%*c", namaD);

        strcpy(baru->namaPrize, namaD);
        baru->kodePrize = kodeD;
        baru->next = head3->top;
        head3->top = baru;
        head3->countPrize = (head3->countPrize) + 1;
    }
    else
    {
        printf("\n--- Stok doorprize penuh ---\n");
    }
}

void popPrize(stack *head3, long long int total)
{
    system("cls");
    prize *temp;
    int success;
    temp = (prize *)malloc(sizeof(prize));

    success = isEmpty(head3);
    if (success == 1)
    {
        printf("\n--- Maaf stok doorprize habis/kosong ---\n\n");
    }
    else
    {
        printf("\n\tSelamat Pelanggan mendapat Doorprize\n");
        printf("\n______________________________________________________\n\n");
        printf("\t\t%s\n\n", head3->top->namaPrize);

        temp = head3->top;
        head3->top = head3->top->next;
        head3->countPrize = head3->countPrize - 1;
        delete temp;
    }
}

void showPrize(stack *head3)
{
    system("cls");
    prize *temp;
    temp = head3->top;
    printf("Tumpukan doorprize dari atas ke bawah : \n");
    printf("________________________________________\n");
    printf("Stok doorprize : %d\n", head3->countPrize);

    printf("\n\t+---+ top\n");

    if (head3->countPrize == 0)
    {
        printf("\n\tNULL\n");
    }
    else
    {
        while (temp)
        {
            printf("\nKode  :\t| %d |", temp->kodePrize);
            printf("\nBarang:\t| %s |", temp->namaPrize);
            printf("\n");
            temp = temp->next;
        }
    }

    printf("\n\t+---+ bottom\n");
}

void deleteList(pelanggan *head, barangJual *head2, stack *head3, queue *myQueue)
{
    pelanggan *pTemp;
    barangJual *pTemp2;
    prize *pTemp3;
    barang *ptemp4;

    while (head != NULL)
    {
        pTemp = head;
        head = head->next;
        free(pTemp);
    }

    while (head2 != NULL)
    {
        pTemp2 = head2;
        head2 = head2->next;
        free(pTemp2);
    }

    while (head3->top != NULL)
    {
        pTemp3 = head3->top;
        head3->top = head3->top->next;
        delete pTemp3;
    }

    while (myQueue != 0)
    {
        ptemp4 = myQueue->front;
        myQueue->front = myQueue->front->next;
        myQueue->count--;
        free(ptemp4);
    }
    myQueue->count = 0;
    myQueue->front = NULL;
    myQueue->rear = NULL;
}