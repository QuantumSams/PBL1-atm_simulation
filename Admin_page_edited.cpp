#include"stdio.h"
#include"conio.h"
#include"stdlib.h"
#include"string.h"
#include"math.h"

typedef char   inform1[20];
typedef double inform2;
typedef double inform3;
typedef char   inform4[100]; //pin o day la mat khau dang nhap
typedef double inform5;
typedef double inform6;  //Danh cho mapin
   

struct cust
{
	inform1 ht;
	inform2 stk;
	inform4 pin;
	inform5 sodu;

	struct cust *next;
}; 

typedef struct cust *list;
list f;

//Chuyen file nho luu y (y la so TK thu tu)


//function in ra giao dich
void Display(list f)
{
	int d=0; list p=f;
	printf("\nSTT\t|HO TEN\t\t\t\t\t\t\tSTK\t\t\tSo du");	
	printf("\n");

	while(p!=NULL)
	{
		d++;
		printf("\n%d\t|%s\t\t\t\t\t\t\t%0.0lf\t\t\t\t\t\t%0.0lf",d,(*p).ht,(*p).stk,(*p).sodu);
		p=(*p).next;
	}
}

//Xuat STK
void Search(list *f, inform2 y)
{
	list p=*f;int d=1;
 	while ((p != NULL) && (*p).stk != y)
 	{
		d++;
		p = (*p).next;
	}
 	
	if(p == NULL)
	{
		printf("\n\t\t\tKhong ton tai tai khoan");
	}

	else
	{
		printf("\nSTT\t|HO TEN\t\t\t\t\t\t\tSTK\t\t\tSo du");
		printf("\n%d\t|%s\t\t\t\t\t\t\t%0.0lf\t\t\t\t\t\t%0.0lf",d,(*p).ht,(*p).stk,(*p).sodu);
		printf("\n\n");
	}
}

//Kiem tra co ton tai STK khong
int Searchextra(list *f, inform2 y)
{
	list p=*f;
 	while ((p != NULL) && (*p).stk != y)
 	{
		p = (*p).next;
	}
 
	if(p == NULL || (*p).stk != y)
	{
		return 1;
	}

	if (p != NULL && (*p).stk == y)
	{
		return 0;
	}
}

//Them phan tu vao dau danh sach
void InsertFirst(list *f, inform1 x, inform2 y, inform4 h, inform5 k)
{ 
	list p = *f;
 	p = (struct cust *)malloc(sizeof(struct cust));
 	strcpy((*p).ht,x); 
	(*p).stk = y; strcpy((*p).pin, h);
	(*p).sodu = k;
 	(*p).next = *f; // 1 �Cho� (*p).next �ch? d?n ph?n t? gi?ng� F �ch?�
 	*f = p; // 2 Cho F ch? d?n ph?n t? gi?ng p ch?.
}

//xoa tk ngan hang
void DeleteElement(list *f, inform2 y)
{ 
	list before, after, p;
	p =* f;
	after =* f;
 	while ((p != NULL) && (*p).stk != y)
 	{
		p= (*p).next;
	}

	while((after != NULL) && (after != p))
	{ 
		before = after; after=(*after).next;
	}

	if(after != NULL)
	{
		if (*f==p) *f=(*p).next;
		else (*before).next=(*p).next; delete p;
	} 
}

void nhanvienit(list f)
{
	int m = 0, t, q, p;
	inform2 y; 
	inform3 z;
	inform1 x;
	inform4 h;
	inform5 k;
	list e;
	
	do  //m==0 de tranh lap lai bi mat
	{
		if(m == 0) 
		{
			printf("\nCHUC NANG\n
			1. Thong tin danh sach\n
			2. Them khach hang moi\n
			3. Tim kiem thong tin khach hang\n
			4. Xoa thong tin khach hang\n
			5. Dong bang tai khoan(chua lam)\n
			6. Danh sach tai khoan bi dong bang(X)\n
			7. Mo khoa tai khoan bi dong bang(X)\n
			8. Lich su giao dich cua khach hang(X)\n
			9. THOAT(DE Phan cuoi cung)");

		 	printf("\nChon:"); scanf("%d", &m);

			if(m < 0 || m > 4)
			{
				do
				{
					printf("\nCHUC NANG\n
					1. Thong tin danh sach\n
					2. Them khach hang moi\n
					3. Tim kiem thong tin khach hang\n
					4. Xoa thong tin khach hang\n
					5. Dong bang tai khoan(chua lam)\n
					6. Danh sach tai khoan bi dong bang(X)\n
					7. Mo koa tai khoan bi dong bang(X)\n
					8. Lich su giao dich cua khach hang(X)");
			
					printf("\nChon lai:"); scanf("%d",&m);
				}
				while(m < 0 || m > 4);
			}
		}
		
		switch(m)
		{
			case 1:Display(f);

			printf("\nXuat thong tin danh sach lan nua?\n1.CO\t\t2.KHONG\n\tChoose:");           //(*1) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(
			scanf("%d",&t);

			if(t==1){m=1; break;}

			if(t==2)
			{
				printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
				printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
				
				scanf("%d",&q);
				
				if(q==1){m=-1;break;}
				if(q==2){m=0;break;}

				while(q != 1 || q != 2)
				{
					printf("\nError,Tiep tuc hay thoat?");
					scanf("%d",&q);
					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}
				}
				break;
			}

			while(t!=1||t!=2)
			{
				printf("\nNhap lai :");                                                          //Chinh int thanh char de tranh bi loi~ while( Nhan xu ly sau)-vd: Nhap chu a thi lap vo han :3
				scanf("%d",&t);
				if(t==1){m=1;break;}
				if(t==2)
				{
					printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
					printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
					scanf("%d",&q);

					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}

				}
				while(q != 1|| q != 2)
				{
					printf("\nError,Tiep tuc hay thoat?");
					scanf("%d",&q);
					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}
				}
				break;
			}                                                                               //(*2) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
			//het case 1
			break;

			case 2:
			printf("\n Them khach hang vao BANK"); 
			
			printf("\nHo Ten:");printf("\t");fflush(stdin);gets(x);
			printf("\nSTK");scanf("%lf",&y);
			printf("\nMat khau");printf("\t");fflush(stdin);gets(h); 
			printf("\nSo tien ban dau");scanf("%lf",&k);
			
			InsertFirst(&f,x,y,h,k);

			printf("\nTiep tuc them khach hang khong?\n1.CO\t\t2.KHONG\n\tChoose:");                     //(*1) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
			scanf("%d",&t);

			if(t==1){m=2;break;}
			if(t==2)
			{
				printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
				printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
				scanf("%d",&q);
				
				if(q==1){m=-1;break;}
				if(q==2){m=0;break;}

				while(q!=1||q!=2)
				{
					printf("\nError,Tiep tuc hay thoat?");
					scanf("%d",&q);
					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}
				}
				break;
			}
			while(t!=1||t!=2)
			{
				printf("\nNhap lai :");                                                          //Chinh int thanh char de tranh bi loi~ while( Nhan xu ly sau)-vd: Nhap chu a thi lap vo han :3
				scanf("%d",&t);
				if(t==1){m=2;break;}
				if(t==2)
				{
					printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
					printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
					scanf("%d",&q);

					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}

				}

				while(q!=1||q!=2)
				{
					printf("\nError,Tiep tuc hay thoat?");
					scanf("%d",&q);
					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}
				}
				break;
			}                                                                                     //(*2) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
			//het case 2
			break;
		
			case 3:printf("\nNhap so tai khoan khach hang can tim kiem:");scanf("%lf",&y);
			Search(&f,y);
			printf("\nTiep tuc kiem tra tai khoan khac khong?\n1.CO\t\t2.KHONG\n\tChoose:");         //(*1) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
			scanf("%d",&t);

			if(t==1){m=3;break;}
			if(t==2)
			{
				printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
				printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
				scanf("%d",&q);

				if(q==1){m=-1;break;}
				if(q==2){m=0;break;}

				while(q!=1||q!=2)
				{
					printf("\nError,Tiep tuc hay thoat?");
					scanf("%d",&q);
					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}

				}
				break;
			}

			while(t!=1||t!=2)
			{
				printf("\nNhap lai :");                                                          //Chinh int thanh char de tranh bi loi~ while( Nhan xu ly sau)-vd: Nhap chu a thi lap vo han :3
				scanf("%d",&t);
				if(t==1){m=3;break;}

				if(t==2)
				{
					printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
					printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
					scanf("%d",&q);

					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}

				}

				while(q!=1||q!=2)
				{
					printf("\nError,Tiep tuc hay thoat?");
					scanf("%d",&q);

					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}
				}
				break;
			}                                                                                //(*2) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
			//het case 3
			break;
		
			case 4: 
			printf("\nXoa tai khoan ma ban muon:");
			scanf("%lf",&y);
			Search(&f,y);
			
			if(Searchextra(&f,y)==1)
			{
				printf("\nTiep tuc xoa them tai khoan khong?\n1.CO\t\t2.KHONG\n\tChoose:");               //(*1) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
				scanf("%d",&t);
				if(t==1){m=4;break;}
				if(t==2)
				{
					printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");                              
					printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
					scanf("%d",&q);

					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}

					while(q!=1||q!=2)
					{
						printf("\nError,Tiep tuc hay thoat?");
						scanf("%d",&q);

						if(q==1){m=-1;break;}
						if(q==2){m=0;break;}
					}
					break;
				}
				while(t!=1||t!=2)
				{
					printf("\nNhap lai :");                                                          //Chinh int thanh char de tranh bi loi~ while( Nhan xu ly sau)-vd: Nhap chu a thi lap vo han :3
					scanf("%d",&t);
					if(t==1){m=4;break;}
					if(t==2)
					{
						printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
						printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
						scanf("%d",&q);

						if(q==1){m=-1;break;}
						if(q==2){m=0;break;}
					}

					while(q!=1||q!=2)
					{
						printf("\nError,Tiep tuc hay thoat?");
						scanf("%d",&q);

						if(q==1){m=-1;break;}
						if(q==2){m=0;break;}
					}
					break;
				}                                                                             //(*2) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
			}
			if(Searchextra(&f,y)==0)
			{	
		
				do
				{
					printf("\n Day co phai la tai khoan se bi xoa vinh vien khong?\n1.Co\t\t2.Khong");
					printf("\n\t Chon");
					scanf("%d",&p);
		
					if(p==1){DeleteElement(&f,y);printf("\n\t\tDa xa tai khoan");break;}
					if(p==2){printf("\nTai khoan khong bi xoa");break;}
	
				}
				while(p!=1||p!=2);
		
				printf("\nTiep tuc xoa tai khoan khong?\n1.CO\t\t2.KHONG\n\tChoose:");                                      //(*2) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
				scanf("%d",&t);

				if(t==1){m=4;break;}
				if(t==2)
				{
					printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
					printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
					scanf("%d",&q);

					if(q==1){m=-1;break;}
					if(q==2){m=0;break;}
					while(q!=1||q!=2)
					{
						printf("\nError,Tiep tuc hay thoat?");
						scanf("%d",&q);

						if(q==1){m=-1;break;}
						if(q==2){m=0;break;}

					}
					break;
				}
				while(t!=1||t!=2)
				{
					printf("\nNhap lai :");                                                          //Chinh int thanh char de tranh bi loi~ while( Nhan xu ly sau)-vd: Nhap chu a thi lap vo han :3
					scanf("%d",&t);
					if(t==1){m=4;break;}
					if(t==2)
					{
						printf("\n\nTiep tuc cong vien cua nhan  vien IT khong?");
						printf("\n1.THOAT\t\t2.TIEP TUC");printf("\nChon:");
						scanf("%d",&q);

						if(q==1){m=-1;break;}
						if(q==2){m=0;break;}

					}

					while(q!=1||q!=2)
					{
						printf("\nError,Tiep tuc hay thoat?");
						scanf("%d",&q);
						if(q==1){m=-1;break;}
						if(q==2){m=0;break;}
					}
					break;
				}
			}
			break;                                                             //(*2) Tu 1 va 2 lap lai hoat dong cua nhanvienit trong tung case(case nao cung co)
		}
	}
	while(m!=-1);                                            //Xu ly xong tat ca case nen them 1 case de huy bo giao dich khi bam lon func nhanvienIT
	 //Them lenh luu file cho NhanvienIT
}
	 
int main()
	 
{
	int m;int t;f=NULL;                                                                                      //Them 1 file co struc f thi bo f=NULL di tranh bi rong(trong file cho NULL san roi luu tru thong tin)
	do
	{
		printf("\n\t\t\t\t\t\tMENU\n");
		printf("\n\t1.Nhan vien IT\n\t2.Khach hang");
		printf("\nXu ly cong viec cho :");
		scanf("%d",&m);
		
		switch(m)
		{
			case 1: nhanvienit(f);                                                                                  //Them file de luu tru thong tin Nhanvien IT
			printf("\n\t\t\tHEY NHAN VIEN BANK\nTiep tuc cong viec khong?\n1.Khong\n2.Co\n\tChoose:");
			scanf("%d",&t);
			if(t==1){m=-1;break;}
			if(t==2){break;}
	
			case 2: break;                                                                                               //Them file de luu tru thong tin khach hang
		}
	}
	while(m>0);
	printf("\n\n\t\t\tDa luu tru thong tin");
}
