#include "Matric.h"
int Len = 0;
int dx[5] = {0, 0, 1, 0, -1}, dy[5] = {0, -1, 0, 1, 0};
int m = 5, n = 5, inx = 1, iny = 1, outx, outy, Result;
int temb[10][10];
int input[10][10]={0};
int x[100], y[100];
/**
  * @brief Calculator
  * @retval None
  */
void calculator(int x, int y)
{
    outx = x;
    outy = y;
    Prepare();
    DFS(inx - 1, iny - 1);
    if (Result == 1)
        tim();
}
void Prepare()
{
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            temb[i][j] = 0;
    temb[inx - 1][iny - 1] = -1;
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
    if ((i < 0) || (i >= m) || (j < 0) || (j >= n))
        return 0;
    if ((input[i][j] != 0) || (temb[i][j] != 0))
        return 0;
    return 1;
}
void tim(void)
{
    x[0] = outx - 1;
    y[0] = outy - 1;
    int i = outx - 1;
    int j = outy - 1;
    int k;
    while (temb[i][j] != -1)
    {
        k = temb[i][j];
        i = i - dx[k];
        j = j - dy[k];
        Len++;
        x[Len] = i;
        y[Len] = j;
    }
}
void Output(void)
{
    if (Result == 1)
    {
        // printf("\nDay CAC TOA DO CAC DIEM TREN DUONG DI THOAT KHOI ME CUNG \n\n");
        // for (int i = Len; i >= 0; i--)
        //     printf("a[%d][%d]-->", x[i], y[i]);
        // printf("\n DUONG DI TRONG ME CUNG LA: \n\n\n");
        // for (int i = 0; i <= 2 * (m - 1); i++)
        // {
        //     for (int j = 0; j <= 2 * (n - 1); j++)
        //     {
        //         printf("%c", OutputImage[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("DO DAI DUONG DI TRONG ME CUNG LA : %d\n", Len);
    }
    // else printf("\nKET LUAN:\t KHONG CO DUONG DI\n\n");
}
