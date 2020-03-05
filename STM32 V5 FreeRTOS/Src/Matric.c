#include "Matric.h"

int G[25][25] = {
{	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	}};
    
void Dijkstra(uint8_t a, uint8_t b, uint8_t (*Move), uint8_t x[], uint8_t y[], uint8_t *Length_way)
{
	// Len[i] - Gia tri nho nhat tu a -> i. Len1 danh dau do dai.
	uint8_t Length_a_to_[25];
	uint8_t Checked[25]; //Danh dau dinh thuoc danh sach dac biet
	uint8_t P[25];		 //truy vet
	for (uint8_t i = 0; i < 25; i++)
	{
		Length_a_to_[i] = 80;
		P[i] = a;
		Checked[i] = 0;
	}
	Length_a_to_[a] = 0; // khoi tao do dai tu a->a = 0
	uint8_t addr_cur = a;

	//while S<>V
	for (uint8_t k = 0; k < 25; k++)
	{
		//tim do dai ngan nhat trong cac dinh
		for (addr_cur = 0; addr_cur < 25; addr_cur++) // tim v thuoc (V-S) va Len[v] < vo cung
			if (!Checked[addr_cur] && Length_a_to_[addr_cur] != 80)
				break;
		for (uint8_t j = addr_cur + 1; j < 25; j++) // tim dinh co Len min
			if (!Checked[j] && Length_a_to_[j] < Length_a_to_[addr_cur])
				addr_cur = j;
		Checked[addr_cur] = 1;

		//--------Tinh do dai tu dinh dang xet toi cac dinh tiep

		for (uint8_t j = 0; j < 25; j++) //thay doi do dai neu co
		{
			if (!Checked[j] && G[addr_cur][j])
				if (Length_a_to_[addr_cur] + G[addr_cur][j] < Length_a_to_[j])
				{
					Length_a_to_[j] = Length_a_to_[addr_cur] + G[addr_cur][j];
					P[j] = addr_cur; //truy vet
				}
		}
	}
	uint8_t stt[5][5] = {
		{0, 1, 2, 3, 4},
		{5, 6, 7, 8, 9},
		{10, 11, 12, 13, 14},
		{15, 16, 17, 18, 19},
		{20, 21, 22, 23, 24}};
	uint8_t temb = b, Length_Way = *Length_way;
	if (!P[temb])
		return;
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
	for (uint8_t i = 0; i < Length_Way; i++)
	{
		if (x[i] == x[i + 1] && y[i] == y[i + 1])
			Move[i] = 0;
		if (x[i] == x[i + 1] && y[i] > y[i + 1])
			Move[i] = 1;
		if (x[i] > x[i + 1] && y[i] == y[i + 1])
			Move[i] = 2;
		if (x[i] == x[i + 1] && y[i] < y[i + 1])
			Move[i] = 3;
		if (x[i] < x[i + 1] && y[i] == y[i + 1])
			Move[i] = 4;
	}
	*Length_way = Length_Way + 1;
}
