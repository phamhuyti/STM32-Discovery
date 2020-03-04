#include<stdio.h>
#include<conio.h>
int Len = 0, dx[5] = { 0, 0, 1, -1, 0 }, dy[5] = { 0, 1, 0, 0, -1 };
int m = 5, n = 5, inx = 1, iny = 1, outx, outy, temb[5][5], Result;
static int input[5][5] = {
	{ 1, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 1 },
	{ 0, 1, 1, 1, 1 },
	{ 0, 1, 0, 0, 1 },
	{ 0, 1, 0, 1, 1 },
};
int x[25], y[25];
char OutputImage[25][25];
void Input(void);
void calculator(void);
void Prepare(void);
void DFS(int i, int j);
int ok(int i, int j);
void tim(void);
void inhinh(int i, int j);
void Output(void);
int main(void) {
	int Run = 13;
	while (Run == 13)
	{
		//Input();
		int moveID[25];
		int move[25];
		outx = 5;
		outy = 4;
		calculator();
		Output();
		printf("\nBan an EnTer de tiep tuc, an phim bat ky de ket thuc.....");
		Run = _getch();
	}
}
void Input()
{
	printf("\nNhap So Hang, So Cot: ");
	m = _getch()-48;
	printf("%d ", m);
	n = _getch()-48;
	printf("%d\n", n);
	printf("Nhap Toa Do Dau va Cuoi: ");
	inx = _getch() - 48;
	printf("%d ", inx);
	iny = _getch() - 48;
	printf("%d ", iny);
	outx = _getch() - 48;
	printf("%d ", outx);
	outy = _getch() - 48;
	printf("%d\n", outy);
	for (int i = 0; i<m; ++i)
		for (int j = 0; j<n; ++j)
		{
			printf("\tPhan Tu Cot %d Hang %d: ",i+1,j+1);
			input[i][j] = _getch() - 48;
			printf("%d\n", input[i][j]);
		}
	printf("\t HINH ANH CUA ME CUNG");
	for (int i = 0; i < m; ++i) {
		printf("\n");
		printf("\t\t\t");
		for (int j = 0; j < n; ++j)
			printf("%d\t", input[i][j]);
	}
}
void calculator()
{
	Prepare();
	DFS(inx - 1, iny - 1);
	if (Result == 1) tim();
	OutputImage[2 * (inx - 1)][2 * (iny - 1)] = '>';
	OutputImage[2 * (outx - 1)][2 * (outy - 1)] = '>';
}
void Prepare()
{
	for (int i = 0; i<m; ++i)
		for (int j = 0; j<n; ++j)
			temb[i][j] = 0;
	for (int i = 0; i <= 2 * (m - 1); ++i)
		for (int j = 0; j <= 2 * (n - 1); ++j)
			if (i % 2 == 0 && j % 2 == 0)
				OutputImage[i][j] = '.';
			else
				OutputImage[i][j] = ' ';
	temb[inx - 1][iny - 1] = 7;
	Result = 0;
}
void DFS(int i, int j)
{
	if ((i == outx - 1) && (j == outy - 1)) 
		Result = 1;
	else
	{
		int k;
		for (k = 1; k <= 4; ++k)
			if (ok(i + dx[k], j + dy[k]))
			{
				temb[i + dx[k]][j + dy[k]] = k;
				DFS(i + dx[k], j + dy[k]);
			}
	}
}
int ok(int i, int j)
{
	if ((i<0) || (i >= m) || (j<0) || (j >= n)) return 0;
	if ((input[i][j] == 0) || (temb[i][j] != 0)) return 0;
	return 1;
}
void tim(void)
{
	x[0] = outx - 1;
	y[0] = outy - 1;
	int i = outx - 1;
	int j = outy - 1;
	int k;
	while (temb[i][j] != 7)
	{
		k = temb[i][j];
		inhinh(i,j);
		i = i - dx[k];
		j = j - dy[k];
		Len++;
		x[Len] = i;
		y[Len] = j;
	}
}
void inhinh(int i, int j)
{
	switch (temb[i][j])
	{
	case 3:
	{
		OutputImage[i * 2][j * 2] = '0';
		OutputImage[i * 2][j * 2 - 1] = '-';
		break;
	}
	case 2:
	{
		OutputImage[i * 2][j * 2] = '0';
		OutputImage[i * 2 - 1][j * 2] = '|';
		break;
	}
	case 1:
	{OutputImage[i * 2][j * 2] = '0';
	OutputImage[i * 2][j * 2 + 1] = '-';
	break;
	}
	case 4:
	{
		OutputImage[i * 2][j * 2] = '0';
		OutputImage[i * 2 + 1][j * 2] = '|';
		break;
	}
	}
}
void Output(void) {
	if(Result != 1) printf("\nKET LUAN:\t KHONG CO DUONG DI\n\n");
	else {
		printf("\nDay CAC TOA DO CAC DIEM TREN DUONG DI THOAT KHOI ME CUNG \n\n");
		for (int i = Len; i >= 0; i--)
			printf("a[%d][%d]-->", x[i], y[i]);
		printf("\n DUONG DI TRONG ME CUNG LA: \n\n\n");
		for (int i = 0; i <= 2 * (m - 1); i++)
		{
			for (int j = 0; j <= 2 * (n - 1); j++)
			{
				printf("%c", OutputImage[i][j]);
			}
			printf("\n");
		}
		printf("DO DAI DUONG DI TRONG ME CUNG LA : %d\n",Len);
	}
}