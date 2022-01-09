#include <iostream>

#include <stdio.h>

#include <Windows.h>

#include <time.h>

#include <conio.h>

#include <locale>

#include <stdlib.h>

#include <vector>

#define INF = 1000000000; // значение "бесконечность"

int** G, * min_e, * sel_e;

bool* used;

int N, z, i, j;

using namespace std;

void printmatrix(int** source, int size);

void generatematrix(int range);

int main()

{

	SetConsoleCP(1251); //Подключение русского языка

	SetConsoleOutputCP(1251);

	printf("Введите количество вершин графа: ");

	scanf_s("%d", &N); //Ввод кол-ва вершин графа

	G = (int**)malloc(N * sizeof(int*)); //Выделяем память под исходную матрицу графа

	for (int i = 0; i < N; i++)

		G[i] = (int*)malloc(N * sizeof(int));

	used = (bool*)malloc(N * sizeof(bool));

	for (int i = 0; i < N; i++)

		used[i] = false;

	min_e = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)

		min_e[i] = 1000000000;

	sel_e = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)

		sel_e[i] = -1;

	//Заполняем исходную матрицу для взвешенного неориентированного графа

	generatematrix(10);

	printf("\nИсходная матрица графа G:\n"); //Вывод матрицы смежности

	printmatrix(G, N);

	printf("\n");

	_getch();

	min_e[0] = 0;

	for (int i = 0; i < N; ++i)

	{

		int v = -1;

		for (int j = 0; j < N; ++j) //Проверяем, является ли вершина пройденной или нет(true/false)

			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))

				v = j;

		if (min_e[v] == 1000000000) //Если не можем строить дерево дальше, то завершаем программу

		{

			printf("\nNo MST!\n");

			exit(0);

		}

		used[v] = true; //Отмечаем вершину, как посещённую

		if (sel_e[v] != -1)

			cout << "Нач. вершина: " << v +1 << " Вес:" << min_e[v] << " Кон. вершина: " << sel_e[v] + 1  << endl;

		for (int to = 0; to < N; ++to) { //Ищем самое короткое ребро у концевой вершины

			if (G[v][to] < min_e[to])

			{

				min_e[to] = G[v][to];

				sel_e[to] = v;

			}

		}

	}

}

void printmatrix(int** source, int size)

{

	printf(" ");

	for (int i = 0; i < size; i++)

		printf(" v%d", i + 1);

	printf("\n");

	for (int i = 0; i < size; i++)

	{

		printf(" v%d ", i + 1);

		for (int j = 0; j < size; j++)

			if (G[i][j] == 1000000000)

				printf(" INF");

			else

				printf("%3d ", source[i][j]);

		printf("\n");

	}

}

void generatematrix(int range) {

	srand(time(NULL));

	for (int i = 0; i < N; i++)

		for (int j = 0; j < N; j++)

			if (i == j) //Ячейки по диоганали 0, т.к нет циклов

				G[i][j] = 0;

			else

			{

				if (rand() % range < 6) //Вероятность заполнения числом 4/10

					G[i][j] = 1 + rand() % range; //В ячейке будет от 0 до 10

				else //Вероятность отсутсвия пути (0) 6/10

					G[i][j] = 1000000000;

				G[j][i] = G[i][j]; //Т.к граф - неориент., происходит зеркальное заполнение

			}

}