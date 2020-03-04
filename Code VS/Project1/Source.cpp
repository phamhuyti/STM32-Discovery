#include <stdio.h>
#include <conio.h>
#include <math.h>
int input[5][5] = {
	{ 2, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0 },
	{ 1, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 1 },
	{ 1, 1, 0, 1, 4 },
},
temb[5][5] = {
	{ 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
};
int moveDir[25];
//x: Hang Y: Cot
int outx = 4, outy = 4, inx = 0, iny = 0, Result = 0, i = 0;

void Run(int x, int y) {
	if (Result == 1) return;
	float Dx = outx - x,
		Dy = outy - y;
	if (x == outx && y == outy) {
		printf("Finish");
		Result = 1;
		return;
	}
	float Dir = atan(Dy / Dx) * 180 / 3.14;
	if (Dx < 0) Dir += 180;
	if (Dy < 0 && Dx >= 0) Dir += 360;
	if (Dir <= 45 || Dir > 315)
	{
		int dx[4] = { 1, 0, 0, -1 }, dy[4] = { 0, 1, -1, 0 };
		for (int k = 0; k < 4; k++)
			if (input[x + dx[k]][y + dy[k]] != 0 && temb[x + dx[k]][y + dy[k]] == 0 && x + dx[k] < 5 && y + dy[k] < 5 &&
				x + dx[k] >= 0 && y + dy[k] >= 0 && Result == 0)
			{
				switch (k)
				{
				case 0:
					moveDir[i] = 2;
					break;
				case 1:
					moveDir[i] = 1;
					break;
				case 2:
					moveDir[i] = 3;
					break;
				case 3:
					moveDir[i] = 4;
					break;
				default:
					break;
				}
				temb[x + dx[k]][y + dy[k]] = 1;
				i++;
				Run(x + dx[k], y + dy[k]);
			}
	}
	if (Dir > 45 && Dir <= 135)
	{
		int dx[4] = { 0, 1, -1, 0 }, dy[4] = { 1, 0, 0, -1 };
		for (int k = 0; k < 4; k++)
			if (input[x + dx[k]][y + dy[k]] != 0 && temb[x + dx[k]][y + dy[k]] == 0 && x + dx[k] < 5 && y + dy[k] < 5 &&
				x + dx[k] >= 0 && y + dy[k] >= 0 && Result == 0)
			{
				switch (k)
				{
				case 0:
					moveDir[i] = 1;
					break;
				case 1:
					moveDir[i] = 2;
					break;
				case 2:
					moveDir[i] = 4;
					break;
				case 3:
					moveDir[i] = 3;
					break;
				default:
					break;
				}
				temb[x + dx[k]][y + dy[k]] = 1;
				i++;
				Run(x + dx[k], y + dy[k]);
			}
	}
	if (Dir > 135 && Dir <= 225)
	{
		int dx[4] = { -1, 0, 0, -1 }, dy[4] = { 0, 1, -1, 0 };
		for (int k = 0; k < 4; k++)
			if (input[x + dx[k]][y + dy[k]] != 0 && temb[x + dx[k]][y + dy[k]] == 0 && x + dx[k] < 5 && y + dy[k] < 5 &&
				x + dx[k] >= 0 && y + dy[k] >= 0 && Result == 0)
			{
				switch (k)
				{
				case 0:
					moveDir[i] = 4;
					break;
				case 1:
					moveDir[i] = 1;
					break;
				case 2:
					moveDir[i] = 3;
					break;
				case 3:
					moveDir[i] = 2;
					break;
				default:
					break;
				}
				temb[x + dx[k]][y + dy[k]] = 1;
				i++;
				Run(x + dx[k], y + dy[k]);
			}
	}
	if (Dir > 225 && Dir <= 315)
	{
		int dx[4] = { 0, -1, 1, 0 }, dy[4] = { -1, 0, 0, 1 };
		for (int k = 0; k < 4; k++)
			if (input[x + dx[k]][y + dy[k]] != 0 && temb[x + dx[k]][y + dy[k]] == 0 && x + dx[k] < 5 && y + dy[k] < 5 &&
				x + dx[k] >= 0 && y + dy[k] >= 0 && Result == 0)
			{
				switch (k)
				{
				case 0:
					moveDir[i] = 3;
					break;
				case 1:
					moveDir[i] = 4;
					break;
				case 2:
					moveDir[i] = 2;
					break;
				case 3:
					moveDir[i] = 1;
					break;
				default:
					break;
				}
				temb[x + dx[k]][y + dy[k]] = 1;
				i++;
				Run(x + dx[k], y + dy[k]);
			}
	}
	if (Result == 0) i--;
}
int main(void) {
	Run(0, 0);
	if (Result == 1)
		for (int i = 0; i < 12; i++)
			if (moveDir[i] != 0)printf("\n%d\n", moveDir[i]);
	_getch();
}
