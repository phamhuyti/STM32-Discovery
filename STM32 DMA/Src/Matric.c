#include "Matric.h"
uint8_t Matric[5][5] =
{ {	1,	0,	1,	1,	1,	},
{	1,	0,	1,	0,	1,	},
{	1,	0,	1,	0,	1,	},
{	1,	0,	1,	0,	1,	},
{	1,	1,	1,	0,	1,	} };
uint8_t G[25][25] = { {	0,	(Matric[0][0] == 1 ? ((Matric[0][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[0][0] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	(Matric[0][1] == 1 ? ((Matric[0][0] == 1) ? 1 : 0) : 0),	0,	(Matric[0][1] == 1 ? ((Matric[0][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[0][1] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	(Matric[0][2] == 1 ? ((Matric[0][1] == 1) ? 1 : 0) : 0),	0,	(Matric[0][2] == 1 ? ((Matric[0][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[0][2] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	(Matric[0][3] == 1 ? ((Matric[0][2] == 1) ? 1 : 0) : 0),	0,	(Matric[0][3] == 1 ? ((Matric[0][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[0][3] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	(Matric[0][4] == 1 ? ((Matric[0][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[0][4] == 1 ? ((Matric[1][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	(Matric[0][0] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[1][0] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][0] == 1 ? ((Matric[2][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	(Matric[1][1] == 1 ? ((Matric[0][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][1] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0),	0,	(Matric[1][1] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][1] == 1 ? ((Matric[2][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	(Matric[1][2] == 1 ? ((Matric[0][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][2] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0),	0,	(Matric[1][2] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][2] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	(Matric[1][3] == 1 ? ((Matric[0][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][3] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0),	0,	(Matric[1][3] == 1 ? ((Matric[1][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][3] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	(Matric[1][4] == 1 ? ((Matric[0][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[1][4] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[1][4] == 1 ? ((Matric[2][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	(Matric[2][0] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[2][0] == 1 ? ((Matric[2][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][0] == 1 ? ((Matric[3][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	(Matric[2][1] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][1] == 1 ? ((Matric[2][0] == 1) ? 1 : 0) : 0),	0,	(Matric[2][1] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	(Matric[2][2] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][2] == 1 ? ((Matric[2][1] == 1) ? 1 : 0) : 0),	0,	(Matric[2][2] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][2] == 1 ? ((Matric[3][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[2][3] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][3] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0),	0,	(Matric[2][3] == 1 ? ((Matric[2][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][3] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[2][4] == 1 ? ((Matric[1][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[2][4] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[2][4] == 1 ? ((Matric[3][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[3][0] == 1 ? ((Matric[2][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[3][0] == 1 ? ((Matric[4][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[3][2] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[3][2] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[3][2] == 1 ? ((Matric[4][2] == 1) ? 1 : 0) : 0),	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[3][3] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[3][3] == 1 ? ((Matric[3][2] == 1) ? 1 : 0) : 0),	0,	(Matric[3][3] == 1 ? ((Matric[3][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[3][3] == 1 ? ((Matric[4][3] == 1) ? 1 : 0) : 0),	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[3][4] == 1 ? ((Matric[2][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[3][4] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[3][4] == 1 ? ((Matric[4][4] == 1) ? 1 : 0) : 0),	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[4][0] == 1 ? ((Matric[3][0] == 1) ? 1 : 0) : 0),	0,	0,	0,	0,	0,	(Matric[4][0] == 1 ? ((Matric[4][1] == 1) ? 1 : 0) : 0),	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[4][1] == 1 ? ((Matric[4][0] == 1) ? 1 : 0) : 0),	0,	(Matric[4][1] == 1 ? ((Matric[4][2] == 1) ? 1 : 0) : 0),	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[4][2] == 1 ? ((Matric[3][2] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[4][2] == 1 ? ((Matric[4][1] == 1) ? 1 : 0) : 0),	0,	(Matric[4][2] == 1 ? ((Matric[4][3] == 1) ? 1 : 0) : 0),	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[4][3] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[4][3] == 1 ? ((Matric[4][2] == 1) ? 1 : 0) : 0),	0,	(Matric[4][3] == 1 ? ((Matric[4][4] == 1) ? 1 : 0) : 0),	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	(Matric[4][4] == 1 ? ((Matric[3][4] == 1) ? 1 : 0) : 0),	0,	0,	0,	(Matric[4][4] == 1 ? ((Matric[4][3] == 1) ? 1 : 0) : 0),	0,	} };


List_move_type Dijkstra(uint8_t a, uint8_t b)
{
	// Len[i] - Gia tri nho nhat tu a -> i. Len1 danh dau do dai.
	uint8_t Length_a_to_[25];
	List_move_type List_Move;
	uint8_t Checked[25]; //Danh dau dinh thuoc danh sach dac biet
	uint8_t P[25];		 //truy vet
	List_Move.Length_way = 0;
	for (uint8_t i = 0; i < 25; i++)
	{
		Length_a_to_[i] = 80;
		P[i] = 80;
		Checked[i] = 0;
		List_Move.Move[i] = 0;
		List_Move.x[i] = 0;
		List_Move.y[i] = 0;
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
	uint8_t temb = b;
	do
	{
		for (uint8_t i = 0; i < 5; i++)
			for (uint8_t j = 0; j < 5; j++)
			{
				if (temb == i*5+j)
				{
					List_Move.x[List_Move.Length_way] = i;
					List_Move.y[List_Move.Length_way] = j;
					goto next;
				}
				if (i == 4 && j == 4 && temb != i * 5 + j)
				{
					List_Move.Length_way = 0;
					goto Endregion;
				}
			}
	next:
		if (List_Move.Length_way > 25 || temb >25)
			goto Endregion;
		temb = P[temb];
		List_Move.Length_way++;
	} while (temb != a);
	for (uint8_t i = 0; i < 5; i++)
		for (uint8_t j = 0; j < 5; j++)
		{
			if (temb == i*5+j)
			{
				List_Move.x[List_Move.Length_way] = i;
				List_Move.y[List_Move.Length_way] = j;
				goto next1;
			}
		}
	next1:
	for (uint8_t i = 0; i < List_Move.Length_way; i++)
	{
		if (List_Move.x[i] == List_Move.x[i + 1] && List_Move.y[i] == List_Move.y[i + 1])
			List_Move.Move[i] = 0;
		if (List_Move.x[i] == List_Move.x[i + 1] && List_Move.y[i] > List_Move.y[i + 1])
			List_Move.Move[i] = 1;
		if (List_Move.x[i] > List_Move.x[i + 1] && List_Move.y[i] == List_Move.y[i + 1])
			List_Move.Move[i] = 2;
		if (List_Move.x[i] == List_Move.x[i + 1] && List_Move.y[i] < List_Move.y[i + 1])
			List_Move.Move[i] = 3;
		if (List_Move.x[i] < List_Move.x[i + 1] && List_Move.y[i] == List_Move.y[i + 1])
			List_Move.Move[i] = 4;
	}
Endregion:
	return List_Move;
}
