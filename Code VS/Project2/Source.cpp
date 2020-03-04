#include <iostream>
#include <conio.h>
#define INP "input.INP"
// #define OUT "output.OUT"
using namespace std;

typedef int item;

int G[25][25] = {
	{ 0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1, },
	{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0, } };
void Dijkstra(int a, int b, int (*Move)[1], int x[], int y[], int *Length_way);//thuat toan Dijkstra

int main(void)
{
	int Move[25][1], x[25], y[25], Length_way = 0;
	for (int i = 0; i < 25; i++) {
		Move[i][0] = 0;
		x[i] = 0;
		y[i] = 0;
	}
	Dijkstra(0, 20, Move, x, y, &Length_way);
	if (!Length_way) cout << "Khong Tim Thay Duong Di !!!";
	for (int i = Length_way-1; i >=0; i--) {
		cout << "(" << x[i] << ":" << y[i] << ")" << "\t" << Move[i][0] << endl;
	}
	_getch();
}


void Dijkstra(int a, int b, int (*Move)[1], int x[], int y[], int *Length_way)
{
	// Len[i] - Gia tri nho nhat tu a -> i. Len1 danh dau do dai.
	int Length_a_to_[25];
	int Checked[25];//Danh dau dinh thuoc danh sach dac biet
	int P[25];//truy vet
	for (int i = 0; i < 25; i++) {
		Length_a_to_[i] = 80;
		P[i] = a;
		Checked[i] = 0;
	}
	Length_a_to_[a] = 0;		// khoi tao do dai tu a->a = 0
	int addr_cur = a;

	//while S<>V
	for (int k = 0; k < 25; k++)
	{
		//tim do dai ngan nhat trong cac dinh		
		for (addr_cur = 0; addr_cur < 25; addr_cur++) // tim v thuoc (V-S) va Len[v] < vo cung
			if (!Checked[addr_cur] && Length_a_to_[addr_cur] != 80)
				break;
		for (int j = addr_cur + 1; j < 25; j++)	// tim dinh co Len min
			if (!Checked[j] && Length_a_to_[j] < Length_a_to_[addr_cur])
				addr_cur = j;
		Checked[addr_cur] = 1;

		//--------Tinh do dai tu dinh dang xet toi cac dinh tiep

		for (int j = 0; j < 25; j++) //thay doi do dai neu co
		{
			if (!Checked[j] && G[addr_cur][j])
				if (Length_a_to_[addr_cur] + G[addr_cur][j] < Length_a_to_[j])
				{
					Length_a_to_[j] = Length_a_to_[addr_cur] + G[addr_cur][j];
					P[j] = addr_cur; //truy vet
				}
		}
	}
	int stt[5][5] = {
		{ 0,	1,	2,	3,	4 },
		{ 5,	6,	7,	8,	9 },
		{ 10,	11,	12,	13,	14 },
		{ 15,	16,	17,	18,	19 },
		{ 20,	21,	22,	23,	24 }
	};
	unsigned int temb = b, Length_Way=*Length_way;
	if (!P[temb]) return;
	while (temb != a)
	{
		for (size_t i = 0; i < 5; i++)
			for (size_t j = 0; j < 5; j++)
			{
				if (temb == stt[i][j])
				{
					x[Length_Way] = i;
					y[Length_Way] = j;
					break;
				}
			}
		temb = P[temb];
		Length_Way++;
	}
	for (int i = 0; i < Length_Way; i++) {
		if (x[i] == x[i + 1] && y[i] == y[i + 1])
			Move[i][0] = 0;
		if (x[i] == x[i + 1] && y[i] > y[i + 1])
			Move[i][0] = 1;
		if (x[i] > x[i + 1] && y[i] == y[i + 1])
			Move[i][0] = 2;
		if (x[i] == x[i + 1] && y[i] < y[i + 1])
			Move[i][0] = 3;
		if (x[i] < x[i + 1] && y[i] == y[i + 1])
			Move[i][0] = 4;
	}
	*Length_way = Length_Way+1;
}
