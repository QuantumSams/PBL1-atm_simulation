#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

//define global
#define MAX_STR 100

//define nhap file
#define MAX_KH  100
#define KH_FILE_IN "data_kh.txt"
#define MAX_FIELD 5

//define phia khach hang
#define MAX_CODE 10
#define B 5
#define LIMIT 5


typedef char   inform1[20];
typedef char   inform2[MAX_STR];
typedef double inform3;
typedef char   inform4[MAX_STR]; //pin o day la mat khau dang nhap
typedef double inform5;
typedef double inform6;  //Danh cho mapin
typedef bool   inform7;  //kiem tra tai khoan co bi vo hieu hoa hay khong

//khoi tao cust
struct cust
{
	inform1 ht;
	inform2 stk;
	inform4 pin;
	inform5 sodu;
    inform7 vohieuhoa;

	struct cust *next;
}; 

//func kh: tao ten list
typedef struct cust *list;
list f = NULL;

//func nhap file: bien global
int KH_DATA_FIELD = 1; // so truong trong file
int SL_KH = 0; // so luong khach hang

//func KH:
void InThongTin1KH(list valid);
list InitList();
int Strcmp(char from_list[MAX_STR], char input[MAX_STR]);
list XacThuc();
int menuChinh(list in);
int isnumString(char in[MAX_STR]);
void doiSoDu(list in, int status);

//func nhap file
int file2str(void);
void addNode(char input_info[MAX_FIELD][MAX_STR]);
int printAllNode();
list InitList();

int main(void)
{
    //test

    file2str();
    XacThuc();
    return 0;
}


void addNode(char a[B][MAX_STR], char b[B][MAX_STR], int c[B], int base)
{
    for(int i = 0; i < base; ++i)
    {
        list tmp = InitList();
        if (tmp == NULL) return;
        strcpy(tmp->stk, a[i]); strcpy(tmp->pin, b[i]);

        tmp->sodu = c[i];
        tmp->vohieuhoa = 0;
        tmp->next = f;
        f = tmp;
    }
    return;
}

void InThongTin1KH(list valid)
{
    if (valid == NULL) return;
    printf("%s   %s   %.f\n", valid->stk, valid->pin, valid->sodu);
    printf("Nhan enter de quay lai menu\n");
    fgetc(stdin);
    menuChinh(valid);
}
// tao cust moi; malloc dia chi; kiem tra NULL
list InitList()
{
    list _ = (struct cust *)malloc(sizeof(struct cust));
    if (_ != NULL) return _;

    printf("Loi\n");
    return NULL;
}

list XacThuc()
{
    char in_acc[MAX_STR]; char in_PIN[MAX_STR];
    
    int lim_value = 0;
    list ptr = NULL;
    
    while(lim_value < LIMIT)
    {    
        printf("Nhap so tai khoan: "); 
        fgets(in_acc, MAX_STR, stdin);

        printf("Nhap ma PIN: "); 
        fgets(in_PIN, MAX_STR, stdin);

        ptr = f;
        int _ = 0;
        while (ptr != NULL)
        {
            if(Strcmp(ptr->stk, in_acc) && Strcmp(ptr->pin, in_PIN))
            {
                if (ptr->vohieuhoa) 
                {
                    //neu tai khoan bi vo hieu hoa -> khong cho vao
                    printf("Tai khoan da bi vo hieu hoa, vui long lien he CSKH\n");
                    XacThuc();
                }
                
                printf("Dang nhap thanh cong!\n");
                _ = 1;
                menuChinh(ptr);
                break;
            }
            else ptr = ptr->next;
        }
        if (_ == 1) break;
        lim_value++;
        printf("STK/PIN khong hop le. Hay nhap lai (con %i lan nhap)\n", LIMIT - lim_value);
        printf("Nhan enter de nhap lai");
        fgetc(stdin);
        printf("_________________________________________________\n");
    }
    return ptr;
}

// kiem tra input nhap vao voi du lieu trong DS LK
// 1 == true; 2 == false
int Strcmp(char from_list[MAX_STR], char input[MAX_STR])
{
    if (strlen(from_list) + 1 != strlen(input)) return 0;

    int i;
    for (i = 0; i < strlen(from_list); i++)
    {
        if ((int)from_list[i] != (int)input[i]) break;
    }
    return i == strlen(from_list);
}

int menuChinh(list in)
{
    if (in == NULL)
    {
        printf("Dang nhap that bai\n");
        return -1;
    }

    int choose = 0;

    do
    {
        printf("   Chao mung, tai khoan #%s\n", in->stk);
        printf("Chon so tuong ung voi cac dich vu duoi day:\n");
        printf("1. Rut tien ra khoi tai khoan\n");
        printf("2. Nap tien vao tai khoan\n");
        printf("3. Xem thong tin\n");
        printf("4. Ket thuc giao dich\n");
        char option[5];
        fgets(option, 5, stdin);
        choose = atoi(option);
        if (strlen(option) <= 2 && strlen(option) > 0 && choose >= 1 && choose <= 4) break;

        printf("Cu phap khong hop le, nhap lai (Nhan enter de tiep tuc)\n");
        fgetc(stdin);
    }
    while(1);

    switch(choose)
    {
        case 1: doiSoDu(in, 0);
        case 2: doiSoDu(in, 1);
        case 3: InThongTin1KH(in);
        case 4: XacThuc();
    }
    return 0;
}
// kiem tra toan bo input co phai la so hay khong
int isnumString(char in[MAX_STR])
{
    int num = strlen(in) - 1;
    int i;

    for (i = 0; i < num; i++)
    {
        if(!isdigit(in[i])) break;
    }
    return (i == num);
}

// 1 == nap; 0 == rut
void doiSoDu(list in, int status)
{
    float diff = 0;
    do
    {
        char tmp[MAX_STR];

        printf("(Nhap 'THOAT' de thoat ra khoi menu)\n");
        printf("Hay nhap so tien can ");
        (status)? printf("nap: ") : printf("rut: ");
        fgets(tmp, MAX_STR, stdin);

        if(strcasecmp(tmp, "THOAT\n") == 0)
        {
            printf("THOAT VE MENU\n");
            menuChinh(in);
        }

        if(isnumString(tmp) == 1)
        {
            diff = atof(tmp);
            break;
        }
        printf("Cu phap khong hop le, nhan ENTER de nhap lai\n");
        fgetc(stdin);
    }
    while (1);

    //Xac thuc ma PIN; 5 lan -> khoa tai khoan, ve menu;

    int PIN_lock = 0;
    do
    {
        char tmp[MAX_STR];
        printf("(Nhap 'THOAT' de thoat ra khoi menu)\n");
        printf("Nhap ma PIN de xac thuc (con %i lan nhap): ", LIMIT - PIN_lock);

        fgets(tmp, MAX_STR, stdin); if(Strcmp(in->pin, tmp)) break;

        PIN_lock++;
        printf("Nhap sai ma PIN, nhan ENTER de nhap lai\n");
        fgetc(stdin);
    } while (PIN_lock < LIMIT);

    //sai qua 5 lan
    if (PIN_lock == LIMIT)
    {
        printf("Nhap sai ma PIN qua nhieu lan, tai khoan da bi vo hieu hoa\n");
        printf("Vui long lien he CSKH de duoc ho tro\n");
        in->vohieuhoa = 1;
        XacThuc();
    }

    //xac nhan giao dich
    do
    {
        char tmp[MAX_STR];

        // truong hop rut tien - kiem tra co du so du hay khong?

        if (status == 0 && in->sodu - diff <= 0)
        {
            printf("So du khong du de thuc hien giao dich\n");
            printf("Nhan ENTER de quay ve Menu\n");
            fgetc(stdin);
            menuChinh(in);
        }


        printf("So du hien tai: %.f\n", in->sodu);
        
        printf("So du sau giao dich: ");
        if (status == 1) printf("%.f\n", in->sodu + diff);
        else printf("%.f\n", in->sodu - diff);

        printf("Xac nhan giao dich (Y/N)?: ");
        fgets(tmp, MAX_STR, stdin);


        if (strlen(tmp) == 2)
        {
            if ((int)tmp[0] == (int) 'n' || (int)tmp[0] == (int) 'N')
            {
                printf("Giao dich da bi huy\n");
            }

            if ((int)tmp[0] == (int) 'y' || (int)tmp[0] == (int) 'Y')
            {
                if (status == 0) diff = -diff;
                in->sodu += diff;
                printf("Giao dich THANH CONG!\n");
            }

            printf("Nhan ENTER de quay ve Menu\n");
            fgetc(stdin);
            menuChinh(in);
        }

        printf("Cu phap khong hop le, nhan ENTER de nhap lai\n");
        fgetc(stdin);
    }
    while (1);
    menuChinh(in);
}


//func nhap file
void addNode(char input_info[MAX_FIELD][MAX_STR])
{
    list tmp = InitList();
    strcpy(tmp->stk, input_info[0]); strcpy(tmp->pin, input_info[1]);
    tmp->sodu = atof(input_info[2]);
    tmp->vohieuhoa = 0;

    tmp->next = f;
    f = tmp;
}

int printAllNode()
{
    list ptr = f;
    if (ptr == NULL) return -1;

    while(ptr != NULL)
    {
        printf("%s   %s   %f\n", ptr->stk, ptr->pin, ptr->sodu);
        ptr = ptr->next;
    }
    return 0;
}
int file2str(void)
{
    char tmp[MAX_STR], KH_DATA_COUNTER[MAX_STR];
    int status_newline;

    FILE *file;
    file = fopen(KH_FILE_IN, "r");
    if (file == NULL) return -1;

    fgets(KH_DATA_COUNTER, MAX_STR, file);

    for (int i = 0; i < strlen(KH_DATA_COUNTER); ++i)
    {
        if ((int)KH_DATA_COUNTER[i] == (int)',')
        {
            KH_DATA_FIELD++;
        }
    }

    while(status_newline != EOF)
    {
        char FILE_TO_STR[MAX_FIELD][MAX_STR];
        int count = 0;

        status_newline = fscanf(file, "%100[^\n]", tmp);

        if (status_newline == 0) status_newline = fscanf(file, "%*c");
        else 
        {   
            char * tmp_token = strtok(tmp, ",");
            while (tmp_token != NULL)
            {
                strcpy(FILE_TO_STR[count], tmp_token);
                count++;
                tmp_token = strtok(NULL, ",");
            }
            addNode(FILE_TO_STR);
            SL_KH++;
        }
    } 

    SL_KH--;
    f = f->next;

    fclose(file);
    return 0;
}
