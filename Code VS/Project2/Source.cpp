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
typedef struct GRAPH
{
	char *name;	// ten cac dinh
	item **G;	// ma tran trong so
	int n;		// so phan tu cua do thi
} Graph;

void input_file(Graph &Gr);// lay du lieu tu file
void input_B_E(Graph Gr, int &a, int &b); //nhap vao dinh dau va cuoi
void Dijkstra(Graph Gr, int a, int b);//thuat toan Dijkstra
item tongthiethai(Graph Gr); //tong quang duong di cua moi dinh (thay the cho vo cung trong ma tran trong so)

int main()
{
	Graph Gr;
	input_file(Gr);
	int a, b;
	cout << endl << "-----Thuat toan Dijkstra-----" << endl;
	input_B_E(Gr, a, b);
	Dijkstra(Gr, a, b);
	_getch();
	return 0;
}

void input_file(Graph &Gr)
{
	ifstream inp(INP);
	/*if (inp == NULL)
	{
		cout << "No found file input";
		return;
	}*/
	inp >> Gr.n;

	Gr.name = new char[Gr.n];
	for (int i = 0; i < Gr.n; i++)
		inp >> Gr.name[i];
	Gr.G = new int *[Gr.n];

	for (int i = 0; i < Gr.n; i++)
	{
		Gr.G[i] = new int[Gr.n];
		for (int j = 0; j < Gr.n; j++)
			inp >> Gr.G[i][j];
	}
	inp.close();
}

void input_B_E(Graph Gr, int &a, int &b)
{
	a = b = 0;
	cout << endl << "Cac dinh danh so tu 1 den " << Gr.n << ".Hoac tu " << Gr.name[0] << " den " << Gr.name[Gr.n - 1] << endl;
	cout << "Nhap dinh bat dau : ";
	while (a<1 || a> Gr.n)
	{
		cin >> a;
		if (a<1 || a> Gr.n)
			cout << "Khong hop le ! \nNhap lai dinh bat dau : ";
	}

	cout << "Nhap dinh ket thuc : ";
	while (b<1 || b> Gr.n)
	{
		cin >> b;
		if (b<1 || b> Gr.n)
			cout << "Khong hop le ! \nNhap lai dinh ket thuc : ";
	}
	a--;
	b--;
}

//tong quang duong di cua moi dinh (thay the cho vo cung trong ma tran trong so)

item tongthiethai(Graph Gr)
{
	item sum = 0;
	for (int i = 0; i < Gr.n; i++)
		for (int j = 0; j < Gr.n; j++)
			sum += Gr.G[i][j];
	return sum;
}


void Dijkstra(Graph Gr, int a, int b)
{
	// Len[i] - Gia tri nho nhat tu a -> i. Len1 danh dau do dai.
	int Len[25];
	int S[25];//Danh dau dinh thuoc danh sach dac biet
	int P[25];//truy vet

	int max = tongthiethai(Gr);
	fill(Len, Len + Gr.n, max); //Gan duong di ban dau = vo cung
	fill(P, P + Gr.n, a);
	fill(S, S + Gr.n, 0); //Danh sach dac biet
	Len[a] = 0;		// khoi tao do dai tu a->a = 0
	int i = a;

	//while S<>V
	for (int k = 0; k < Gr.n; k++)
	{
		char *s = new char[100];
		char vocung = '~', gach[10] = "  -  ";

		//tim do dai ngan nhat trong cac dinh		
		for (i = 0; i < Gr.n; i++) // tim v thuoc (V-S) va Len[v] < vo cung
			if (!S[i] && Len[i] != max)
				break;
		for (int j = i + 1; j < Gr.n; j++)	// tim dinh co Len min
			if (!S[j] && Len[j] < Len[i])
				i = j;
		S[i] = 1;

		//--------Tinh do dai tu dinh dang xet toi cac dinh tiep

		for (int j = 0; j < Gr.n; j++) //thay doi do dai neu co
		{
			if (!S[j] && Gr.G[i][j])
				if (Len[i] + Gr.G[i][j] < Len[j])
				{
					Len[j] = Len[i] + Gr.G[i][j];
					P[j] = i; //truy vet
				}
		}
	}
	i = b;
	int move[25], j = 0;
	cout << i;
	move[0] = i;
	while (i != a)
	{
		j++;
		move[j] = P[i];
		cout << "<--" << move[j];
		i = P[i];
	}
	cout << endl;
	for (int i = j; i >= 0; i--) {
		if(move[i]>=0 && move[i]<100)cout << move[i]<<"-->";
	}
}
