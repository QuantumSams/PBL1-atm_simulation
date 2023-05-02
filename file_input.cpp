#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 100
#define MAX_KH  100
#define KH_FILE_IN "data_kh.txt"

typedef char   STR[MAX_STR];

typedef char   inform1[20];
typedef char   inform2[MAX_STR];
typedef double inform3;
typedef char   inform4[MAX_STR]; //pin o day la mat khau dang nhap
typedef double inform5;
typedef double inform6;  //Danh cho mapin
typedef bool   inform7;  //kiem tra tai khoan co bi vo hieu hoa hay khong

struct cust
{
	inform1 ht;
	inform2 stk;
	inform4 pin;
	inform5 sodu;
    inform7 vohieuhoa;

	struct cust *next;
}; 

typedef struct cust *list;
list f = NULL;

STR FILE_TO_STR[MAX_KH];
int KH_DATA_FIELD = 1;
int SL_KH = 0;

int file2str(void);
void addNode();
int printAllNode();
list InitList();


int main(void)
{
    file2str();
    addNode();
    printAllNode();
    return 0;

}

void addNode()
{
    for(int i = 0; i < KH_DATA_FIELD * SL_KH; i += KH_DATA_FIELD)
    {
        list tmp = InitList();
        if (tmp == NULL) return;
        strcpy(tmp->stk, FILE_TO_STR[i]); strcpy(tmp->pin, FILE_TO_STR[i + 1]);

        tmp->sodu = atof(FILE_TO_STR[i + 2]);
        tmp->vohieuhoa = 0;
        tmp->next = f;
        f = tmp;
    }
    return;
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
list InitList()
{
    list _ = (struct cust *)malloc(sizeof(struct cust));
    if (_ != NULL) return _;

    printf("Loi\n");
    return NULL;
}
int file2str(void)

{
    FILE *f;
    f = fopen(KH_FILE_IN, "r");
    if (f == NULL) return -1;

    STR tmp, KH_DATA_COUNTER;
    int status_newline;

    fgets(KH_DATA_COUNTER, MAX_STR, f);

    for (int i = 0; i < strlen(KH_DATA_COUNTER); ++i)
    {
        if ((int)KH_DATA_COUNTER[i] == (int)',')
        {
            KH_DATA_FIELD++;
        }
    }
    do
    {
        status_newline = fscanf(f, "%100[^\n]", tmp);

        if (status_newline == 0) 
        {
            status_newline = fscanf(f, "%*c");
        }
        else 
        {   
            char * tmp_token = strtok(tmp, ",");
            
            while (tmp_token != NULL)
            {
                strcpy(FILE_TO_STR[SL_KH], tmp_token);
                SL_KH ++;
                tmp_token = strtok(NULL, ",");
            }
        }
    } while(status_newline != EOF);

    SL_KH--; 
    SL_KH /= KH_DATA_FIELD;

    fclose(f);
    return 0;
}