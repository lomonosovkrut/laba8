#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <queue>
std::queue <int> Q;
int** createG(int size) {
	int** G = NULL;
	G = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		G[i] = (int*)malloc(size * sizeof(int));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			G[i][j] = rand() % 2;
			if (i == j) {
				G[i][j] = 0;
			}
			G[j][i] = G[i][j];
		}
	}
	return G;
}

void printG(int** G, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d", G[i][j]);
		}
		printf("\n");
	}
	return;
}

void bfs(int** G, int size, int s, int* vis) {
	Q.push(s);
	vis[s] = 1;
	printf("%d ", s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < size; i++) {
			if (G[s][i] == 1 && vis[i] == 0) {
				Q.push(i);
				vis[i] = 1;
				printf("%d ", i);
			}
		}
	}
}
int main()
{
	int s = 0;
	setlocale(LC_ALL, "Rus");
	int size = 5;
	int** G1 = createG(size);
	printf("Введите размер матрицы \n");
	scanf("%d", &size);
	printf("Матрица 1\n");
	printG(G1, size);

	int* vis = NULL;
	vis = (int*)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		vis[i] = 0;
	}
	printf("Список кратчайшего (пути обход в ширину): ");
	bfs(G1, size, s, vis);
	return 0;
}