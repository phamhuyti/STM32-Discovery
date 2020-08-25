#include "Matric.h"
uint8_t Matric[5][5] =
{ 
    {	1,	1,	1,	1,	1,	},
    {	1,	1,	1,	1,	1,	},
    {	1,	1,	1,	1,	1,	},
    {	1,	1,	1,	1,	1,	},
    {	1,	1,	1,	1,	1,	} 
};
uint8_t G[25][25] = 
{{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	}};


void CreateMatricFromRFIDMatric(void) {
	G[1][0] = (Matric[0][1] == 1 ? ((Matric[0][0] == 1) ? 1 : 0) : 0);
	G[5][0] = (Matric[0][0] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0);
	G[0][1] = (Matric[0][0] == 1 ? ((Matric[0][1] == 1) ? 1 : 0) : 0);
	G[2][1] = (Matric[0][2] == 1 ? ((Matric[0][1] == 1) ? 1 : 0) : 0);
	G[6][1] = (Matric[1][1] == 1 ? ((Matric[0][1] == 1) ? 1 : 0) : 0);
	G[1][2] = (Matric[0][1] == 1 ? ((Matric[0][2] == 1) ? 1 : 0) : 0);
	G[3][2] = (Matric[0][3] == 1 ? ((Matric[0][2] == 1) ? 1 : 0) : 0);
	G[7][2] = (Matric[1][2] == 1 ? ((Matric[0][2] == 1) ? 1 : 0) : 0);
	G[2][3] = (Matric[0][2] == 1 ? ((Matric[0][3] == 1) ? 1 : 0) : 0);
	G[4][3] = (Matric[0][4] == 1 ? ((Matric[0][3] == 1) ? 1 : 0) : 0);
	G[8][3] = (Matric[1][3] == 1 ? ((Matric[0][3] == 1) ? 1 : 0) : 0);
	G[3][4] = (Matric[0][3] == 1 ? ((Matric[0][4] == 1) ? 1 : 0) : 0);
	G[9][4] = (Matric[1][4] == 1 ? ((Matric[0][4] == 1) ? 1 : 0) : 0);
	G[0][5] = (Matric[0][0] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0);
	G[6][5] = (Matric[1][1] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0);
	G[10][5] = (Matric[2][0] == 1 ? ((Matric[1][0] == 1) ? 1 : 0) : 0);
	G[1][6] = (Matric[0][1] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0);
	G[5][6] = (Matric[1][0] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0);
	G[7][6] = (Matric[1][2] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0);
	G[11][6] = (Matric[2][1] == 1 ? ((Matric[1][1] == 1) ? 1 : 0) : 0);
	G[2][7] = (Matric[0][2] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0);
	G[6][7] = (Matric[1][1] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0);
	G[8][7] = (Matric[1][3] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0);
	G[12][7] = (Matric[2][2] == 1 ? ((Matric[1][2] == 1) ? 1 : 0) : 0);
	G[3][8] = (Matric[0][3] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0);
	G[7][8] = (Matric[1][2] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0);
	G[9][8] = (Matric[1][4] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0);
	G[13][8] = (Matric[2][3] == 1 ? ((Matric[1][3] == 1) ? 1 : 0) : 0);
	G[4][9] = (Matric[0][4] == 1 ? ((Matric[1][4] == 1) ? 1 : 0) : 0);
	G[8][9] = (Matric[1][3] == 1 ? ((Matric[1][4] == 1) ? 1 : 0) : 0);
	G[14][9] = (Matric[2][4] == 1 ? ((Matric[1][4] == 1) ? 1 : 0) : 0);
	G[5][10] = (Matric[1][0] == 1 ? ((Matric[2][0] == 1) ? 1 : 0) : 0);
	G[11][10] = (Matric[2][1] == 1 ? ((Matric[2][0] == 1) ? 1 : 0) : 0);
	G[15][10] = (Matric[3][0] == 1 ? ((Matric[2][0] == 1) ? 1 : 0) : 0);
	G[6][11] = (Matric[1][1] == 1 ? ((Matric[2][1] == 1) ? 1 : 0) : 0);
	G[10][11] = (Matric[2][0] == 1 ? ((Matric[2][1] == 1) ? 1 : 0) : 0);
	G[12][11] = (Matric[2][2] == 1 ? ((Matric[2][1] == 1) ? 1 : 0) : 0);
	G[16][11] = (Matric[3][1]==1?((Matric[2][1]==1)?1:0):0);
	G[7][12] = (Matric[1][2] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0);
	G[11][12] = (Matric[2][1] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0);
	G[13][12] = (Matric[2][3] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0);
	G[17][12] = (Matric[3][2] == 1 ? ((Matric[2][2] == 1) ? 1 : 0) : 0);
	G[8][13] = (Matric[1][3] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0);
	G[12][13] = (Matric[2][2] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0);
	G[14][13] = (Matric[2][4] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0);
	G[18][13] = (Matric[3][3] == 1 ? ((Matric[2][3] == 1) ? 1 : 0) : 0);
	G[9][14] = (Matric[1][4] == 1 ? ((Matric[2][4] == 1) ? 1 : 0) : 0);
	G[13][14] = (Matric[2][3] == 1 ? ((Matric[2][4] == 1) ? 1 : 0) : 0);
	G[19][14] = (Matric[3][4] == 1 ? ((Matric[2][4] == 1) ? 1 : 0) : 0);
	G[10][15] = (Matric[2][0] == 1 ? ((Matric[3][0] == 1) ? 1 : 0) : 0);
	G[16][15] = (Matric[3][1]==1?((Matric[3][0]==1)?1:0):0),
	G[20][15] = (Matric[4][0] == 1 ? ((Matric[3][0] == 1) ? 1 : 0) : 0);
	G[11][16] = (Matric[3][1]==1?((Matric[2][1]==1)?1:0):0); 
	G[15][16] = (Matric[3][1]==1?((Matric[3][0]==1)?1:0):0);
	G[17][16] = (Matric[3][1]==1?((Matric[3][2]==1)?1:0):0);
	G[21][16] = (Matric[3][1]==1?((Matric[4][1]==1)?1:0):0);
	G[12][17] = (Matric[2][2] == 1 ? ((Matric[3][2] == 1) ? 1 : 0) : 0);
	G[16][17] = (Matric[3][1]==1?((Matric[3][2]==1)?1:0):0),
	G[18][17] = (Matric[3][3] == 1 ? ((Matric[3][2] == 1) ? 1 : 0) : 0);
	G[22][17] = (Matric[4][2] == 1 ? ((Matric[3][2] == 1) ? 1 : 0) : 0);
	G[13][18] = (Matric[2][3] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0);
	G[17][18] = (Matric[3][2] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0);
	G[19][18] = (Matric[3][4] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0);
	G[23][18] = (Matric[4][3] == 1 ? ((Matric[3][3] == 1) ? 1 : 0) : 0);
	G[14][19] = (Matric[2][4] == 1 ? ((Matric[3][4] == 1) ? 1 : 0) : 0);
	G[18][19] = (Matric[3][3] == 1 ? ((Matric[3][4] == 1) ? 1 : 0) : 0);
	G[24][19] = (Matric[4][4] == 1 ? ((Matric[3][4] == 1) ? 1 : 0) : 0);
	G[15][20] = (Matric[3][0] == 1 ? ((Matric[4][0] == 1) ? 1 : 0) : 0);
	G[21][20] = (Matric[4][1] == 1 ? ((Matric[4][0] == 1) ? 1 : 0) : 0);
	G[16][21] = (Matric[3][1]==1?((Matric[4][1]==1)?1:0):0),
	G[20][21] = (Matric[4][0] == 1 ? ((Matric[4][1] == 1) ? 1 : 0) : 0);
	G[22][21] = (Matric[4][2] == 1 ? ((Matric[4][1] == 1) ? 1 : 0) : 0);
	G[17][22] = (Matric[3][2] == 1 ? ((Matric[4][2] == 1) ? 1 : 0) : 0);
	G[21][22] = (Matric[4][1] == 1 ? ((Matric[4][2] == 1) ? 1 : 0) : 0);
	G[23][22] = (Matric[4][3] == 1 ? ((Matric[4][2] == 1) ? 1 : 0) : 0);
	G[18][23] = (Matric[3][3] == 1 ? ((Matric[4][3] == 1) ? 1 : 0) : 0);
	G[22][23] = (Matric[4][2] == 1 ? ((Matric[4][3] == 1) ? 1 : 0) : 0);
	G[24][23] = (Matric[4][4] == 1 ? ((Matric[4][3] == 1) ? 1 : 0) : 0);
	G[19][24] = (Matric[3][4] == 1 ? ((Matric[4][4] == 1) ? 1 : 0) : 0);
	G[23][24] = (Matric[4][3] == 1 ? ((Matric[4][4] == 1) ? 1 : 0) : 0);
}


void UpdateMatric(uint8_t x, uint8_t y, uint8_t val)
{
	Matric[x-0x30][y-0x30]= val-0x30;
	CreateMatricFromRFIDMatric();
}

List_move_type Dijkstra(uint8_t a, uint8_t b)
{
	// Tao ma tran the hien moi qua he cua cac the
	CreateMatricFromRFIDMatric();
	// tạo bien luu huong di sao khi tim duoc duong
	List_move_type List_Move;
	// 	uint8_t Length_a_to_[i] - khoang cach nho nhat tu a -> i
	uint8_t Length_a_to_[25];
	uint8_t Checked[25]; //Danh dau dinh da duoc duyet qua
	uint8_t P[25];		 //Luu lai duong duong di
	//Do dai duong di sao khi tinh toan
	List_Move.Length_way = 0;
	// Dat gia tri ban dau cua cac bien
	for (uint8_t i = 0; i < 25; i++)
	{
		Length_a_to_[i] = 80;
		P[i] = 80;
		Checked[i] = 0;
		List_Move.Move[i] = 0;
		List_Move.x[i] = 0;
		List_Move.y[i] = 0;
	}
	Length_a_to_[a] = 0; // Do dai tu a->a = 0
	// Dat diem xet dau tien la a
	uint8_t addr_cur = a;

	//while S<>V
	// for (uint8_t k = 0; k < 25; k++)
	while (addr_cur != b && addr_cur != 25)
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
					P[j] = addr_cur; //Luu duong di hien tai
				}
		}
		// if(addr_cur == 24) break;
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
	// for (uint8_t i = 0; i < 5; i++)
	// 	for (uint8_t j = 0; j < 5; j++)
	// 	{
	// 		if (temb == i*5+j)
	// 		{
	// 			List_Move.x[List_Move.Length_way] = i;
	// 			List_Move.y[List_Move.Length_way] = j;
	// 			goto next1;
	// 		}
	// 	}
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
