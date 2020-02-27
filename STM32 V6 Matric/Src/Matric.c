#include "Matric.h"

uint8_t Len = 0;
uint8_t m = 5, n = 5, inx = 1, iny = 1, outx, outy, Result;
uint8_t temb[5][5];
static uint64_t input[5][5] = {
    {1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
};
uint8_t x[25], y[25];
/**
  * @brief Calculator
  * @retval None
  */
void calculator(uint8_t x, uint8_t y, uint8_t output[])
{
    outx = x;
    outy = y;
    Prepare();
    DFS(inx - 1, iny - 1);
    if (Result == 1)
        tim();
    Output(output);
}
void Prepare()
{
    for (uint8_t i = 0; i < m; ++i)
        for (uint8_t j = 0; j < n; ++j)
            temb[i][j] = 0;
    temb[inx - 1][iny - 1] = 5;
    Result = 0;
}
void DFS(uint8_t i, uint8_t j)
{
    if ((i == outx - 1) && (j == outy - 1))
        Result = 1;
    else
    {
        uint8_t k;
        int8_t dx[5] = {0, 0, 1, 0, -1}, dy[5] = {0, -1, 0, 1, 0};
        for (k = 1; k <= 4; ++k)
            if (ok(i + dx[k], j + dy[k]))
            {
                temb[i + dx[k]][j + dy[k]] = k;
                DFS(i + dx[k], j + dy[k]);
            }
    }
}
int ok(int8_t i, int8_t j)
{
    if ((i < 0) || (i >= m) || (j < 0) || (j >= n))
        return 0;
    if ((input[i][j] == 0) || (temb[i][j] != 0))
        return 0;
    return 1;
}
void tim(void)
{
    x[0] = outx - 1;
    y[0] = outy - 1;
    int8_t dx[5] = {0, 0, 1, 0, -1}, dy[5] = {0, -1, 0, 1, 0};
    uint8_t i = outx - 1;
    uint8_t j = outy - 1;
    uint8_t k;
    while (temb[i][j] != 5)
    {
        k = temb[i][j];
        i = i - dx[k];
        j = j - dy[k];
        Len++;
        x[Len] = i;
        y[Len] = j;
    }
}
void Output(uint8_t a[])
{
    if (Result == 1)
    {
        // printf("\nDay CAC TOA DO CAC DIEM TREN DUONG DI THOAT KHOI ME CUNG \n\n");
        uint8_t j = 0;
        for (int8_t i = Len - 1; i >= 0; i--)
        {
            // printf("a[%d][%d]-->", x[i], y[i]);
            if (x[i] == x[i + 1] && y[i] == y[i + 1])
                a[j] = 0;
            if (x[i] == x[i + 1] && y[i] > y[i + 1])
                a[j] = 1;
            if (x[i] > x[i + 1] && y[i] == y[i + 1])
                a[j] = 2;
            if (x[i] == x[i + 1] && y[i] < y[i + 1])
                a[j] = 3;
            if (x[i] < x[i + 1] && y[i] == y[i + 1])
                a[j] = 4;
            j++;
        }
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
