#include "main.h"
// static uint64_t input[5][5] = {
//     {0xd9c86f81ff, 0x39a5ae82b0, 0x39d39481ff, 0xb9326a8263, 0x298f6d814a},
//     {0x796ebb812d, 0x192f6c82d8, 0xc95e678272, 0x199fdc82d8, 0xd7440b3ea6},
//     {0x99c7dd3bb8, 0x77f488353e, 0x9725083d87, 0xb98d6e4319, 0x69236f88ad},
//     {0x2952ab8151, 0x49d8948184, 0xe92d628224, 0x59dfc683c3, 0x6969818100},
//     {0x9fdca82bc, 0x998cca825d, 0xa91e6d8258, 0x17c10e3ee6, 0x896f0dc52e},
// };
static uint64_t input[5][5] = {
    {0xd9c86f81ff, 0x39a5ae82b0, 0x39d39481ff, 0, 0x298f6d814a},
    {0x796ebb812d, 0x192f6c82d8, 0xc95e678272, 0, 0xd7440b3ea6},
    {0x99c7dd3bb8, 0x77f488353e, 0x9725083d87, 0, 0x69236f88ad},
    {0, 0, 0, 0, 0},
    {0x9fdca82bc, 0x998cca825d, 0xa91e6d8258, 0x17c10e3ee6, 0x896f0dc52e},
};
void calculator(uint8_t x, uint8_t y, uint8_t move[], uint64_t moveID[]);
void Prepare(void);
void DFS(uint8_t i, uint8_t j);
int ok(int8_t i, int8_t j);
void tim(void);
void Output(uint8_t move[], uint64_t moveID[]);
