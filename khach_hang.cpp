#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <time.h>

//define global
#define MAX_CHUOI_KI_TU 100
#define VND 1000
#define MIN_DANG_KY 4
#define MAX_DANG_KY 64

//define nhap file
#define MAX_KH  100
#define KH_FILE_IN "data_kh.txt"
#define MAX_TRUONG 10

//define phia khach hang
#define MAX_CODE 10
#define GIOI_HAN_PIN 5
#define GIOI_HAN_GIAO_DICH_1_NGAY 5
#define GIOI_HAN_SO_TIEN_1_NGAY 200000

//define lich su giao dich
#define RANDOM 10000

//define in bang
#define DANG_KY_MOI "|------------------------- LUU Y KHI TAO TAI KHOAN NGAN HANG ---------------------\n|                                                                                |\n|  Vui long dien chinh xac thong tin ve ho ten                                   |\n|                                                                                |\n|  So tai khoan va ma PIN la cac ky tu so, toi thieu 6 ki tu, toi da 64 ky tu    |\n|                                                                                |\n|  Vui long ghi nho so tai khoan va ma PIN sau khi nhap de tranh khoa tai khoan  |\n|                                                                                |\n|--------------------------------------------------------------------------------\n"

#define CLRSCR "\e[1;1H\e[2J"
#define CHIEU_DAI_BANG 78

#define DASH_LICH_SU " --------------------------------------------------------------------------"
#define MENU "________________________________________________________________________________\n|                                   |                                           |\n|       ____ ___  ______     __     |    Vui long chon so ung voi cac dich vu   |\n|       | __ |_ _|  _ \\     / /     |                 duoi day:                 |\n|       |  _ \\| || | | \\ \\ / /      |                                           |\n|       | |_| | || |_| |\\ V /       |    1. Rut tien              2. Nap tien   |\n|       |____/___|____/  \\_/        |                                           |\n|                                   |    3. Xem thong tin         4. Ket thuc   |\n|     54 Nguyen Luong Bang - DN     |                                           |\n|_______________________________________________________________________________|\n"
#define NGAN_DONG "_________________________________________________\n"
#define HEADER_LSGD "\n|    STK    | So GD | DD/MM/YYYY | HH:MM:SS | Chenh lech SD |  SD bay gio  |\n"

#define DANG_NHAP_HEADER "\n-------------------------- DIEM GIAO DICH ATM BIDV - DUT -----------------------\n"
#define DANG_NHAP_TK " Nhap so tai khoan: "
#define DANG_NHAP_PIN " Nhap ma PIN: "

#define KHUNG_THONG_TIN_KHACH_HANG "|-------------------------- THONG TIN/LICH SU GIAO DICH KH ----------------------\n|                                                                                |\n|  So tai khoan giao dich: %12s                                          |\n|                                                                                |\n|  So du hien tai: %9i VND                                                 |\n|                                                                                |\n|--------------------------------------------------------------------------------\n"
#define LUU_Y_GIAO_DICH "|-------------------------- LUU Y KHI THUC HIEN GIAO DICH -----------------------\n|                                                                                |\n|  Nhap 'THOAT' neu muon tro ve MENU trong qua trinh giao dich                   |\n|                                                                                |\n|  Gioi han so tien giao dich trong 1 ngay: %i VND                        |\n|                                                                                |\n|  Nhap sai ma PIN nhieu lan co the dan den tai khoan bi vo hieu hoa             |\n|                                                                                |\n|--------------------------------------------------------------------------------\n", GIOI_HAN_SO_TIEN_1_NGAY * VND

#define CHU_Y_ENTER "\n|------------------------------------ CHU Y!!! ----------------------------------\n|                                                                                |\n|  Cu phap khong hop le                                                          |\n|                                                                                |\n|  Nhan ENTER de nhap lai                                                        |\n|                                                                                |\n|--------------------------------------------------------------------------------\n"
#define TAI_KHOAN_TAM_KHOA "|------------------------------- TAI KHOAN TAM KHOA -----------------------------\n|                                                                                |\n|  Nhap sai ma PIN qua nhieu lan, tai khoan da bi vo hieu hoa                    |\n|                                                                                |\n|  Vui long lien he CSKH de duoc ho tro                                          |\n|                                                                                |\n|--------------------------------------------------------------------------------\n"

#define XAC_NHAN_GIAO_DICH "|-------------------------------- Xac nhan giao dich -----------------------------\n|                                                                                |\n|  So du hien tai:      %12i                                             |\n|                                                                                |\n|  So du sau giao dich: %12i                                             |\n|                                                                                |\n|  Chon Y de xac nhan giao dich | Chon N de huy giao dich                        |\n|                                                                                |\n|--------------------------------------------------------------------------------\n\n"
#define GD_THANH_CONG "///////////////////////////////// GIAO DICH THANH CONG! //////////////////////////////\n                   Chan thanh cam on quy khach da tin dung dich vu cua\n                                 ____ ___ ______     __    \n                                | __ |_ _|  _ \\     / /    \n                                |  _ \\| || | | \\ \\ / /   \n                                | |_| | || |_| |\\ V /      \n                                |____/___|____/  \\_/       \n"

typedef struct
{
    char so_tai_khoan[MAX_CHUOI_KI_TU];
    int random;
    char ngay[MAX_CHUOI_KI_TU];
    char thoi_gian[MAX_CHUOI_KI_TU];

    int bien_dong_so_du;
    int so_du_con_lai;

}LICH_SU_GIAO_DICH;


typedef char   inform2[MAX_CHUOI_KI_TU];
typedef double inform3;
typedef char   inform4[MAX_CHUOI_KI_TU]; //pin o day la mat khau dang nhap
typedef double inform5;
typedef double inform6;  //Danh cho mapin


//khoi tao cust
struct cust
{
	char ho_ten[MAX_CHUOI_KI_TU];
	inform2 stk;
	inform4 pin;
	inform5 sodu;
    bool vohieuhoa;
    int han_muc_giao_dich;

    LICH_SU_GIAO_DICH bay_gio[GIOI_HAN_GIAO_DICH_1_NGAY];
	struct cust *next;
}; 

//func toan cuc
int manHinhChao();

//func kh: tao ten list
typedef struct cust *list;
list f = NULL;

//func nhap file: bien global
int KH_DATA_FIELD = 1; // so truong trong file
int SL_KH = 0; // so luong khach hang

//func KH:
void InThongTin1KH(list valid); // in thong tin LSGD va thong tin tai khoan
list TaoDSLKnull(); // tao DSLK rong
int Strcmp(char from_list[MAX_CHUOI_KI_TU], char input[MAX_CHUOI_KI_TU]); //so sanh 2 chuoi ky tu
void dangNhap(); // dang nhap
int menuChinh(list in);
int cophaiSo(char in[MAX_CHUOI_KI_TU]); // kiem tra chuoi co phai la so
void doiSoDu(list in, int status); // nap tien, rut tien
int xacnhanYN(); //chon Y/y de dong y; N/n de huy

//func nhap file
int nhapFile(void); // nhap file du lieu khach hang
void themDLsangDSLK(char input_info[MAX_TRUONG][MAX_CHUOI_KI_TU]);
int inDSLK(); // in toan bo DSLK

//func lich su giao dich
void layLS(list in, int diff, int index); // lay thong tin sau moi giao dich thanh cong
void inLS(LICH_SU_GIAO_DICH bay_gio); // in thong tin giao dich 1 khach hang

//func in man hinh
void inCHUY(const char * chu_y); // in ra man hinh canh bao + yeu cau nhan ENTER de tiep tuc

//func dang ky moi tai khoan
void dangKy();
int xacthucDangKy(char ho_ten[MAX_CHUOI_KI_TU], char stk[MAX_CHUOI_KI_TU], char pin[MAX_CHUOI_KI_TU]);
int trunglapDangKy(char stk[MAX_CHUOI_KI_TU], char pin[MAX_CHUOI_KI_TU]);
void INHOAten(char in[MAX_CHUOI_KI_TU]);

//func xuat file
void xuatFileKH();

int main(void)
{
    if(nhapFile() == -1)
    {
        printf("Khong co du lieu khach hang (fix bug)\n");
        return -1;
    }

    manHinhChao();
}

void InThongTin1KH(list hop_le)
{
    if (hop_le == NULL) return;
    
    printf("Ho va Ten chu tai khoan: %s\n", hop_le->ho_ten);
    printf(KHUNG_THONG_TIN_KHACH_HANG, hop_le->stk, (int)(hop_le->sodu) * VND);
    
    printf(DASH_LICH_SU);
    printf(HEADER_LSGD);
    printf(DASH_LICH_SU);

    for (int i = 0; i < GIOI_HAN_GIAO_DICH_1_NGAY - 1 - hop_le->han_muc_giao_dich; i++)
    {
        inLS(hop_le->bay_gio[i]);
    }

    printf("\nNhan enter de quay lai menu\n");
    fgetc(stdin);
    menuChinh(hop_le);
}
// tao cust moi; malloc dia chi; kiem tra NULL
list TaoDSLKnull()
{
    list _ = (struct cust *)malloc(sizeof(struct cust));
    if (_ != NULL) return _;

    printf("Loi\n");
    return NULL;
}

void dangNhap()
{
    // printf(CLRSCR);
    char in_acc[MAX_CHUOI_KI_TU]; char in_PIN[MAX_CHUOI_KI_TU];
    
    list ptr = f;
    
    printf(DANG_NHAP_HEADER);

    printf(DANG_NHAP_TK); 
    fgets(in_acc, MAX_CHUOI_KI_TU, stdin);

    printf(DANG_NHAP_PIN);
    fgets(in_PIN, MAX_CHUOI_KI_TU, stdin);

    while (ptr != NULL)
    {
        if(Strcmp(ptr->stk, in_acc) && Strcmp(ptr->pin, in_PIN))
        {
            if (ptr->vohieuhoa) 
            {
                //neu tai khoan bi vo hieu hoa -> khong cho vao
                printf(TAI_KHOAN_TAM_KHOA);
                manHinhChao();
            }
            menuChinh(ptr);
            break;
        }
        else ptr = ptr->next;
    }
    inCHUY("Cu phap khong hop le");
    manHinhChao();
    return;
}


// kiem tra input nhap vao voi du lieu trong DS LK
// 1 == true; 0 == false
int Strcmp(char chuoi_dslk[MAX_CHUOI_KI_TU], char chuoi_nhap[MAX_CHUOI_KI_TU])
{
    if (strlen(chuoi_dslk) + 1 != strlen(chuoi_nhap)) return 0;

    int i;
    for (i = 0; i < strlen(chuoi_dslk); i++)
    {
        if ((int)chuoi_dslk[i] != (int)chuoi_nhap[i]) break;
    }
    return i == strlen(chuoi_dslk);
}

int menuChinh(list in)
{
    printf(CLRSCR);

    if (in == NULL)
    {
        printf("Dang nhap that bai\n");
        return -1;
    }

    printf("Dang nhap thanh cong!\n");

    int choose = 0;

    do
    {
        printf(MENU);

        printf("\nLua chon: ");
        char option[5];
        fgets(option, 5, stdin);
        choose = atoi(option);
        if (strlen(option) <= 2 && strlen(option) > 0 && choose >= 1 && choose <= 4) break;

        inCHUY("Cu phap khong hop le");
        printf(CLRSCR);
    }
    while(1);
    printf("\n");

    switch(choose)
    {
        case 1: doiSoDu(in, 0);
        case 2: doiSoDu(in, 1);
        case 3: InThongTin1KH(in);
        case 4: manHinhChao();
    }
    return 0;
}

// kiem tra toan bo input co phai la so hay khong
int cophaiSo(char in[MAX_CHUOI_KI_TU])
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
    //kiem tra han muc giao dich
    if(in->han_muc_giao_dich < 0)
    {
        inCHUY("Vuot qua han muc giao dich, khong the thuc hien yeu cau");
        menuChinh(in);
    }
    
    float diff = 0;
    do
    {
        char tmp[MAX_CHUOI_KI_TU];

        printf(CLRSCR);
        printf(LUU_Y_GIAO_DICH);

        printf("\n  Nhap so tien can ");
        (status)? printf("nap(>= 1000 VND): ") : printf("rut(>= 1000 VND): ");
        fgets(tmp, MAX_CHUOI_KI_TU, stdin);

        if(strcasecmp(tmp, "THOAT\n") == 0)
        {
            printf("THOAT VE MENU\n");
            menuChinh(in);
        }

        if(cophaiSo(tmp) == 1 && atof(tmp) >= VND && atof(tmp) <= GIOI_HAN_SO_TIEN_1_NGAY * VND)
        {
            diff = atof(tmp) / 1000;
            break;
        }
        inCHUY("Lua chon khong hop le");
    }
    while (1);

    //Xac thuc ma PIN; 5 lan -> khoa tai khoan, ve menu;

    int PIN_lock = 0;
    do
    {
        char tmp[MAX_CHUOI_KI_TU];
        printf("\n  Nhap ma PIN de xac thuc (con %i lan nhap): ", GIOI_HAN_PIN - PIN_lock);
        fgets(tmp, MAX_CHUOI_KI_TU, stdin);
        
        if(strcasecmp(tmp, "THOAT\n") == 0)
        {
            printf("THOAT VE MENU\n");
            menuChinh(in);
        }

        if(Strcmp(in->pin, tmp)) 
        {
            printf(CLRSCR);
            break;
        }

        PIN_lock++;
        inCHUY("Ma PIN khong trung khop");

    } while (PIN_lock < GIOI_HAN_PIN);

    //sai qua 5 lan
    if (PIN_lock == GIOI_HAN_PIN)
    {
        printf(TAI_KHOAN_TAM_KHOA);
        in->vohieuhoa = 1;
        manHinhChao();
    }

    //xac nhan giao dich
    do
    {
        // truong hop rut tien - kiem tra co du so du hay khong?

        if (status == 0 && in->sodu - diff <= 0)
        {
            inCHUY("So du khong du de thuc hien giao dich");
            menuChinh(in);
        }

        int _;
        if (status == 1) _ = (in->sodu + diff) * VND;
        else _ = (in->sodu - diff) * VND;

        printf("\n");
        printf(XAC_NHAN_GIAO_DICH, (int)in->sodu * VND, _);        

        int co_phai_y_n = xacnhanYN();
        if (co_phai_y_n == -1) continue;

        else
        {
            if (co_phai_y_n == 0)
            {
                printf("Giao dich da bi huy\n");
            }

            else
            {
                if(status == 0) diff = -diff;
                in->sodu = in->sodu + diff;

                layLS(in, diff, GIOI_HAN_GIAO_DICH_1_NGAY - 1 - in->han_muc_giao_dich);

                in->han_muc_giao_dich--;
                printf(GD_THANH_CONG);
            }
            printf("\nNhan ENTER de quay ve Menu\n");
            fgetc(stdin);
            menuChinh(in);
        }
    }
    while (1);
    menuChinh(in);
}


//func nhap file
void themDLsangDSLK(char input_info[MAX_TRUONG][MAX_CHUOI_KI_TU])
{
    list tmp = TaoDSLKnull();

    strcpy(tmp->stk, input_info[0]); strcpy(tmp->pin, input_info[1]);

    tmp->sodu = atof(input_info[2]);
    tmp->vohieuhoa = atof(input_info[3]);
    strcpy(tmp->ho_ten, input_info[4]);

    tmp->han_muc_giao_dich = GIOI_HAN_GIAO_DICH_1_NGAY - 1;

    tmp->next = f;
    f = tmp;
}

int inDSLK()
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


int nhapFile(void)
{
    char tmp[MAX_CHUOI_KI_TU], KH_DATA_COUNTER[MAX_CHUOI_KI_TU];
    int status_newline;

    FILE *file;
    file = fopen(KH_FILE_IN, "r");
    if (file == NULL) return -1; // kiem tra file co san hay khong

    //kiem tra file co noi dung hay khong
    fseek(file, 0, SEEK_END);
    if(ftell(file) == 0) return -1;

    fseek(file, 0, SEEK_SET);


    fgets(KH_DATA_COUNTER, MAX_CHUOI_KI_TU, file);

    for (int i = 0; i < strlen(KH_DATA_COUNTER); ++i)
    {
        if ((int)KH_DATA_COUNTER[i] == (int)',')
        {
            KH_DATA_FIELD++;
        }
    }

    while(status_newline != EOF)
    {
        char FILE_TO_STR[MAX_TRUONG][MAX_CHUOI_KI_TU];
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
            themDLsangDSLK(FILE_TO_STR);
            SL_KH++;
        }
    } 

    SL_KH--;
    f = f->next;

    fclose(file);
    return 0;
}

void layLS(list in, int diff, int index)
{
    strcpy(in->bay_gio[index].so_tai_khoan, in->stk);

    in->bay_gio[index].so_du_con_lai = in->sodu;
    in->bay_gio[index].bien_dong_so_du = diff;

    time_t thoi_gian = time(NULL);
    struct tm *now = localtime(&thoi_gian);

    srand(thoi_gian);
    in->bay_gio[index].random = rand() % RANDOM;

    strftime(in->bay_gio[index].ngay, MAX_CHUOI_KI_TU, "%d/%m/%Y", now);
    strftime(in->bay_gio[index].thoi_gian, MAX_CHUOI_KI_TU, "%X", now);

    printf("%05d | %s | %s | ", in->bay_gio[index].random, in->bay_gio[index].ngay,
              in->bay_gio[index].thoi_gian);

    if(diff > 0) printf("+");
    printf("%9i VND| %9i VND\n\n", in->bay_gio[index].bien_dong_so_du * VND, in->bay_gio[index].so_du_con_lai * VND);
}


void inLS(LICH_SU_GIAO_DICH bay_gio)
{
    printf("\n| %9s | %05d | %s | %s | ",bay_gio.so_tai_khoan, bay_gio.random, bay_gio.ngay, bay_gio.thoi_gian);

    if(bay_gio.bien_dong_so_du > 0) printf("+");
    else 
    {
        bay_gio.bien_dong_so_du = -bay_gio.bien_dong_so_du;
        printf("-");
    };

    printf("%9i VND| %9i VND|\n", bay_gio.bien_dong_so_du * VND, bay_gio.so_du_con_lai * VND);

    printf(DASH_LICH_SU);

}
int xacnhanYN()
{
    printf("Xac nhan giao dich (Y/N)?: ");
    char tmp[MAX_CHUOI_KI_TU]; fgets(tmp, MAX_CHUOI_KI_TU, stdin);

    printf("\n");

    if (strcasecmp(tmp, "y\n") == 0) return 1;
    else if (strcasecmp(tmp, "n\n") == 0) return 0;

    inCHUY("Lua chon khong hop le");
    return -1;
}

void inCHUY(const char * chu_y)
{    
    int len = CHIEU_DAI_BANG - strlen(chu_y);
    printf("\n|------------------------------------ CHU Y!!! ----------------------------------\n|                                                                                |\n|  %s", chu_y);

    for(int i = 0; i < len; i++)
    {
        printf(" ");
    }

    printf("|\n");

    printf("|                                                                                |\n|  Vui long nhan ENTER de nhap lai                                               |\n|                                                                                |\n|--------------------------------------------------------------------------------\n");
    fgetc(stdin);
}

void dangKy()
{
    char input_info[MAX_TRUONG][MAX_CHUOI_KI_TU];
    
    printf(DANG_KY_MOI);

        printf("Nhap HO VA TEN: "); fgets(input_info[4], MAX_CHUOI_KI_TU, stdin);
        printf("Nhap STK (4 - 64 ky tu): "); fgets(input_info[0], MAX_CHUOI_KI_TU, stdin);
        printf("Nhap PIN (4 - 64 ky tu): "); fgets(input_info[1], MAX_CHUOI_KI_TU, stdin);
        
        // bo "\n" sau len gets
        input_info[0][strcspn(input_info[0], "\n")] = 0;
        input_info[1][strcspn(input_info[1], "\n")] = 0;
        input_info[4][strcspn(input_info[4], "\n")] = 0;

        if(xacthucDangKy(input_info[4], input_info[0], input_info[1]))
        {
            //so du  = 0
            strcpy(input_info[2], "0");
            //vo hieu hoa = 0
            strcpy(input_info[3], "0");

            INHOAten(input_info[4]);

            themDLsangDSLK(input_info);
            printf(CLRSCR);
            printf("Tai khoan tao thanh cong!\nNhan Enter de quay ve MENU\n");
            fgetc(stdin);
        }
        manHinhChao();
}

int xacthucDangKy(char ho_ten[MAX_CHUOI_KI_TU], char stk[MAX_CHUOI_KI_TU], char pin[MAX_CHUOI_KI_TU])
{
    //kiem tra ten tai khoan
    for (int kiem_tra_chu = 0; kiem_tra_chu < strlen(ho_ten) - 1; ++kiem_tra_chu)
    {
        if(!isalpha(ho_ten[kiem_tra_chu]) && !isblank(ho_ten[kiem_tra_chu]))
        {
            inCHUY("Ten khong phu hop");
            return 0;
        }
    }
    // kiem tra do dai, ky tu cua STK
    if(strlen(stk) > MAX_DANG_KY || strlen(stk) < MIN_DANG_KY || cophaiSo(stk) == 0)
    {
        inCHUY("So tai khoan khong phu hop");
        return 0;
    } 
    // kiem tra do dai, ky tu cua PIN
    if(strlen(pin) > MAX_DANG_KY || strlen(pin) < MIN_DANG_KY || cophaiSo(pin) == 0)
    {
        inCHUY("Ma PIN khong phu hop");
        return 0;
    }

    if(trunglapDangKy(stk, pin) == 0)
    {
        inCHUY("STK/ma PIN bi trung");
        return 0;
    }
    return 1;
}

//kiem tra thong tin co bi trung lap hay khong
int trunglapDangKy(char stk[MAX_CHUOI_KI_TU], char pin[MAX_CHUOI_KI_TU])
{
    list verify = f;

    while(verify != NULL && strcmp(stk, verify->stk) != 0 && strcmp(pin, verify->pin) != 0)
    {
        verify = verify->next;
    }
    return verify == NULL;
}

int manHinhChao()
{
    // printf(CLRSCR);
    int choose;
    do
    {
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. (Admin): tat may\n");

        printf("\nLua chon: ");
        char option[5];
        fgets(option, 5, stdin);
        choose = atoi(option);
        if (strlen(option) <= 2 && strlen(option) > 0 && choose >= 1 && choose <= 3) break;

        inCHUY("Cu phap khong hop le");
        printf(CLRSCR);
    }

    while(1);
    printf("\n");

    switch(choose)
    {
        case 1: dangNhap();
        case 2: dangKy();
        case 3:
         xuatFileKH();
         return 1;
    }
    return 0;
}

void xuatFileKH()
{
    list out = f; 
    FILE * thoat; thoat = freopen(KH_FILE_IN, "w", stdout);

    printf("stk,pin,sd,vohieuhoa,hoten\n");
    while (out != NULL)
    {
        printf("%s,%s,%.f,%i,%s\n", out->stk, out->pin, out->sodu, out->vohieuhoa, out->ho_ten);
        out = out->next;
    }

    fclose(thoat);
    return;
}

void INHOAten(char in[MAX_CHUOI_KI_TU])
{
    char tmp[MAX_CHUOI_KI_TU];
    int i;

    for(i = 0; i < strlen(in); i++)
    {
       tmp[i] = toupper(in[i]);
    }

    tmp[i] = '\0';
    strcpy(in, tmp);
}