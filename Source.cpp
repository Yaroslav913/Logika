#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <time.h>

using namespace std;


void bfsd(int** mas1, int n, int* dist, int v)
{
	queue<int> q;
	q.push(v);
	dist[v] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (mas1[v][i] > 0 && dist[i] > dist[v] + mas1[v][i])
			{
				q.push(i);
				dist[i] = dist[v] + mas1[v][i];
			}
		}
	}
}


void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	int n, num, v; //N-���-�� ������, num-������� ��� �����, v-������� ��� �����
	int** mas1, ** mas2;
	printf("\n������� ������ �������: ");
	scanf_s("%d", &n);
	int* dist = (int*)malloc(n * sizeof(int));
	int* ecst = (int*)malloc(n * sizeof(int));
	int rad, diam;
	diam = -1;
	rad = 11;
	mas1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		mas1[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		mas1[i][i] = 0;
		for (int j = i + 1; j < n; j++)
		{
			mas1[i][j] = rand() % 11;
			mas1[j][i] = mas1[i][j];
		}
	}
	printf("\n\n����� ������� ���������:\n ");
	for (int i = 0; i < n; i++) { // ����� ������ ���������
		printf("\n");
		for (int j = 0; j < n; j++) {
			printf("%d ", mas1[i][j]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		dist[i] = 1000;
	}
	for (int i = 0; i < n; i++)
	{
		ecst[i] = -1;
	}
	for (int i = 0; i < n; i++) {
		bfsd(mas1, n, dist, i);
		printf("\n���������� �� ������� %d �� ���������:\n", i + 1);
		for (int j = 0; j < n; j++)
		{
			printf("%d ", dist[j]);
			if (dist[j] > ecst[i]) {
				ecst[i] = dist[j];
			}
		}
		for (int k = 0; k < n; k++)
		{
			dist[k] = 1000;
		}
	}
	printf("\n��������������\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", ecst[i]);
	}
	for (int i = 0; i < n; i++) {
		if (diam < ecst[i]) {
			diam = ecst[i];
		}
	}
	for (int i = 0; i < n; i++) {
		if (rad > ecst[i]) {
			rad = ecst[i];
		}
	}
	printf("\n�������: %d \n", diam);
	printf("������: %d \n", rad);
	printf("����������� �������: \n");
	for (int i = 0; i < n; i++) {
		if (rad == ecst[i]) {
			printf("%d ", i + 1);
		}
	}
	printf("\n������������ �������: \n");
	for (int i = 0; i < n; i++) {
		if (diam == ecst[i]) {
			printf("%d ", i + 1);
		}
	}
	int* deg = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		deg[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mas1[i][j] != 0) {
				deg[i] = deg[i] + 1;
			}
		}
	}
	printf("\n������� ");
	for (int i = 0; i < n; i++) {
		if (deg[i] == 0) {
			printf("%d", i + 1);
		}
	}
	printf(" - �������������");
	printf("\n������� ");
	for (int i = 0; i < n; i++) {
		if (deg[i] == 1) {
			printf("%d", i + 1);
		}
	}
	printf(" - ��������");
	printf("\n������� ");
	for (int i = 0; i < n; i++) {
		if (deg[i] == (n - 1)) {
			printf("%d ", i + 1);
		}
	}
	printf(" - ������������");
}