#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <conio.h>
#define INP "input.INP"
// #define OUT "output.OUT"
using namespace std;

typedef int item;
//typedef struct GRAPH
//{
//	char *name;	// ten cac dinh
//	item **G;	// ma tran trong so
//	int n;		// so phan tu cua do thi
//} Graph;
int stt[5][5] = {
	{ 0,	1,	2,	3,	4 },
	{ 5,	6,	7,	8,	9 },
	{ 10,	11,	12,	13,	14 },
	{ 15,	16,	17,	18,	19 },
	{ 20,	21,	22,	23,	24 }
};
int n = 25, G[25][25] = {
	{0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0}
};
void input_B_E(int &a, int &b); //nhap vao dinh dau va cuoi
void Dijkstra(int a, int b);//thuat toan Dijkstra
item tongthiethai(); //tong quang duong di cua moi dinh (thay the cho vo cung trong ma tran trong so)

int main()
{
	int a, b;
	cout << endl << "-----Thuat toan Dijkstra-----" << endl;
	input_B_E(a, b);
	Dijkstra(a, b);
	_getch();
	return 0;
}

void input_B_E(int &a, int &b)
{
	a = b = 0;
	cout << endl << "Cac dinh danh so tu 1 den " << n << ".Hoac tu 1 den 25" << endl;
	cout << "Nhap dinh bat dau : ";
	while (a<1 || a> n)
	{
		cin >> a;
		if (a<1 || a> n)
			cout << "Khong hop le ! \nNhap lai dinh bat dau : ";
	}

	cout << "Nhap dinh ket thuc : ";
	while (b<1 || b> n)
	{
		cin >> b;
		if (b<1 || b> n)
			cout << "Khong hop le ! \nNhap lai dinh ket thuc : ";
	}
	a--;
	b--;
}

//tong quang duong di cua moi dinh (thay the cho vo cung trong ma tran trong so)

item tongthiethai()
{
	item sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sum += G[i][j];
	return sum;
}


void Dijkstra(int a, int b)
{
	// Len[i] - Gia tri nho nhat tu a -> i. Len1 danh dau do dai.
	int Len[25];
	int S[25];//Danh dau dinh thuoc danh sach dac biet
	int P[25];//truy vet

	int max = tongthiethai();
	fill(Len, Len + n, max); //Gan duong di ban dau = vo cung
	fill(P, P + n, a);
	fill(S, S + n, 0); //Danh sach dac biet
	Len[a] = 0;		// khoi tao do dai tu a->a = 0
	int addr_cur = a;

	//while S<>V
	for (int k = 0; k < n; k++)
	{
		//tim do dai ngan nhat trong cac dinh		
		for (addr_cur = 0; addr_cur < n; addr_cur++) // tim v thuoc (V-S) va Len[v] < vo cung
			if (!S[addr_cur] && Len[addr_cur] != max)
				break;
		for (int j = addr_cur + 1; j < n; j++)	// tim dinh co Len min
			if (!S[j] && Len[j] < Len[addr_cur])
				addr_cur = j;
		S[addr_cur] = 1;

		//--------Tinh do dai tu dinh dang xet toi cac dinh tiep

		for (int j = 0; j < n; j++) //thay doi do dai neu co
		{
			if (!S[j] && G[addr_cur][j])
				if (Len[addr_cur] + G[addr_cur][j] < Len[j])
				{
					Len[j] = Len[addr_cur] + G[addr_cur][j];
					P[j] = addr_cur; //truy vet
				}
		}
	}
	int temb = b;
	int move[25], j = 0;
	cout << temb;
	move[0] = temb;
	while (temb != a)
	{
		j++;
		move[j] = P[temb];
		cout << "<--" << move[j];
		temb = P[temb];
	}
	cout << endl;
	for (int k = j; k >= 0; k--) {
		if (move[k] >= 0 && move[k] < 25)
			for (int i = 0; i < 5; i++)
				for (int i = 0; i < 5; i++)
					name;
	}
}
