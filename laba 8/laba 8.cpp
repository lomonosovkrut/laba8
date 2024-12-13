#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <queue> 
#include <locale.h>
#include <time.h>

// Структура для реализации собственной очереди
typedef struct Queue {
    int* items;   // Массив для хранения элементов очереди
    int front;    // Индекс начала очереди
    int rear;     // Индекс конца очереди
    int maxsize;  // Максимальный размер очереди
} Queue;

// Структура для представления графа
typedef struct {
    int** adjacencyMatrix; // Матрица смежности графа
    int vertexCount;       // Количество вершин в графе
} Graph;

// Функции для работы с собственной очередью

// Создание очереди заданного размера
Queue* createQueue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->maxsize = size;
    q->front = -1; // Очередь изначально пуста
    q->rear = -1;  // Очередь изначально пуста
    q->items = (int*)malloc(size * sizeof(int)); // Выделение памяти под элементы
    return q;
}

// Проверка, заполнена ли очередь
bool isFull(Queue* q) {
    return q->rear == q->maxsize - 1; // Если конец очереди достиг максимального размера
}

// Проверка, пуста ли очередь
bool isEmpty(Queue* q) {
    return q->front == -1 || q->front > q->rear; // Если очередь пуста или все элементы удалены
}

// Добавление элемента в очередь
void enqueue(Queue* q, int value) {
    if (!isFull(q)) { // Если очередь не заполнена
        if (q->front == -1) q->front = 0; // Если очередь пуста, устанавливаем начало
        q->rear++; // Увеличиваем индекс конца
        q->items[q->rear] = value; // Добавляем элемент
    }
}

// Удаление элемента из очереди
int dequeue(Queue* q) {
    if (!isEmpty(q)) { // Если очередь не пуста
        int item = q->items[q->front]; // Получаем элемент из начала очереди
        q->front++; // Сдвигаем начало очереди
        return item;
    }
    return -1; // Возвращаем -1 в случае ошибки
}

// Генерация матрицы смежности для графа
int** generateAdjacencyMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*)); // Выделение памяти под строки матрицы
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int)); // Выделение памяти под столбцы
        for (int j = 0; j < n; j++) {
            // Заполняем матрицу случайными значениями (1 - есть ребро, 0 - нет ребра)
            matrix[i][j] = (i != j && rand() % 2) ? 1 : 0; // Ребра между разными вершинами
        }
    }
    return matrix;
}

// Вывод списка смежности графа
void printAdjacencyList(Graph* graph) {
    printf("\nСписок смежности:\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("%d: ", i); // Выводим вершину
        for (int j = 0; j < graph->vertexCount; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) { // Если есть ребро
                printf("%d ", j); // Выводим смежную вершину
            }
        }
        printf("\n");
    }
}

// Обход графа в ширину по списку смежности
void bfsUsingAdjacencyList(Graph* graph, int start) {
    bool* visited = (bool*)malloc(graph->vertexCount * sizeof(bool)); // Массив для отслеживания посещенных вершин
    for (int i = 0; i < graph->vertexCount; i++) visited[i] = false; // Изначально все вершины не посещены

    std::queue<int> q; // Создаем стандартную очередь
    visited[start] = true; // Помечаем стартовую вершину как посещенную
    q.push(start); // Добавляем стартовую вершину в очередь

    while (!q.empty()) { // Пока очередь не пуста
        int node = q.front(); // Получаем вершину из начала очереди
        q.pop(); // Удаляем вершину из очереди
        printf("%d ", node); // Выводим вершину

        // Проходим по всем смежным вершинам
        for (int i = 0; i < graph->vertexCount; i++) {
            if (graph->adjacencyMatrix[node][i] == 1 && !visited[i]) { // Если есть ребро и вершина не посещена
                visited[i] = true; // Помечаем вершину как посещенную
                q.push(i); // Добавляем вершину в очередь
            }
        }
    }
    free(visited); // Освобождаем память
}

// Обход графа в ширину с использованием стандартной очереди C++
void bfsUsingStdQueue(int** matrix, int n, int start) {
    bool* visited = (bool*)malloc(n * sizeof(bool)); // Массив для отслеживания посещенных вершин
    for (int i = 0; i < n; i++) visited[i] = false; // Изначально все вершины не посещены

    std::queue<int> q; // Создаем стандартную очередь
    visited[start] = true; // Помечаем стартовую вершину как посещенную
    q.push(start); // Добавляем стартовую вершину в очередь

    while (!q.empty()) { // Пока очередь не пуста
        int node = q.front(); // Получаем вершину из начала очереди
        q.pop(); // Удаляем вершину из очереди
        printf("%d ", node); // Выводим вершину

        for (int i = 0; i < n; i++) {
            if (matrix[node][i] == 1 && !visited[i]) { // Если есть ребро и вершина не посещена
                visited[i] = true; // Помечаем вершину как посещенную
                q.push(i); // Добавляем вершину в очередь
            }
        }
    }
    free(visited); // Освобождаем память
}

// Обход графа в ширину с использованием собственной очереди
void bfsUsingCustomQueue(int** matrix, int n, int start) {
    bool* visited = (bool*)malloc(n * sizeof(bool)); // Массив для отслеживания посещенных вершин
    for (int i = 0; i < n; i++) visited[i] = false; // Изначально все вершины не посещены

    Queue* q = createQueue(n); // Создаем собственную очередь
    visited[start] = true; // Помечаем стартовую вершину как посещенную
    enqueue(q, start); // Добавляем стартовую вершину в очередь

    while (!isEmpty(q)) { // Пока очередь не пуста
        int node = dequeue(q); // Получаем вершину из начала очереди
        printf("%d ", node); // Выводим вершину

        for (int i = 0; i < n; i++) {
            if (matrix[node][i] == 1 && !visited[i]) { // Если есть ребро и вершина не посещена
                visited[i] = true; // Помечаем вершину как посещенную
                enqueue(q, i); // Добавляем вершину в очередь
            }
        }
    }
    free(visited); // Освобождаем память
    free(q->items); // Освобождаем память, выделенную под элементы очереди
    free(q); // Освобождаем память, выделенную под очередь
}

// Основная функция
int main() {
    setlocale(LC_ALL, "RUS"); // Устанавливаем локаль для вывода на русском языке
    srand(time(NULL)); // Инициализируем генератор случайных чисел
    int n;

    // Ввод количества вершин графа
    printf("Введите количество вершин графа: ");
    scanf("%d", &n);

    // Создание графа
    Graph graph;
    graph.vertexCount = n; // Устанавливаем количество вершин
    graph.adjacencyMatrix = generateAdjacencyMatrix(n); // Генерируем матрицу смежности

    // Вывод матрицы смежности
    printf("Матрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph.adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    // Вывод списка смежности
    printAdjacencyList(&graph);

    // Обход графа в ширину с использованием стандартной очереди
    printf("\nОбход в ширину с использованием стандартной очереди:\n");
    clock_t start_std = clock(); // Начало измерения времени
    bfsUsingStdQueue(graph.adjacencyMatrix, n, 0); // Запуск обхода
    clock_t end_std = clock(); // Конец измерения времени
    double time_std = (double)(end_std - start_std) / CLOCKS_PER_SEC; // Вычисление времени выполнения
    printf("\nВремя выполнения (стандартная очередь): %.6f секунд\n", time_std);

    // Обход графа в ширину с использованием собственной очереди
    printf("\nОбход в ширину с использованием самодельной очереди:\n");
    clock_t start_custom = clock(); // Начало измерения времени
    bfsUsingCustomQueue(graph.adjacencyMatrix, n, 0); // Запуск обхода
    clock_t end_custom = clock(); // Конец измерения времени
    double time_custom = (double)(end_custom - start_custom) / CLOCKS_PER_SEC; // Вычисление времени выполнения
    printf("\nВремя выполнения (самодельная очередь): %.6f секунд\n", time_custom);

    // Обход графа в ширину по списку смежности
    printf("\nОбход в ширину по списку смежности:\n");
    clock_t start_list = clock(); // Начало измерения времени
    bfsUsingAdjacencyList(&graph, 0); // Запуск обхода
    clock_t end_list = clock(); // Конец измерения времени
    double time_list = (double)(end_list - start_list) / CLOCKS_PER_SEC; // Вычисление времени выполнения
    printf("\nВремя выполнения (список смежности): %.6f секунд\n", time_list);

    // Освобождение памяти, выделенной под матрицу смежности
    for (int i = 0; i < n; i++) {
        free(graph.adjacencyMatrix[i]);
    }
    free(graph.adjacencyMatrix);
    return 0;
}