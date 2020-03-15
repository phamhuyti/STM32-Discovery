#pragma once
#include <iostream>
#include <conio.h>
using namespace std;
typedef int item;
typedef struct
{
	int Move[25]; //List Step Move
	int x[25];    //Descartes X
	int y[25];    //Descartes Y
	int Length_way;
} List_move_type;
//thuat toan Dijkstra
List_move_type Dijkstra(int a, int b);
