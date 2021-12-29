
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <locale.h>
#include <stack>

using namespace std;

typedef struct Node {
	int vertex;
	struct Node* next;
} Node;

void add_Node_to_beginning(Node** head, int data) //������� ���������� ���� � ������
{
	Node* tmp_node = (Node*)malloc(sizeof(Node)); // ������� ����� ����
	tmp_node->vertex = data;
	tmp_node->next = (*head); //����������� ��������� tmp ����� ����. ����
	(*head) = tmp_node; //����������� ��������� head ����� tmp
} //����� ������ �� ������� tmp ������������

Node* findLastHead(Node* head) { //����� ������ ���������� ��������
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

void add_Node_to_end(Node* head, int data) { //������� ���������� ������ ���� � �����
	Node* last = findLastHead(head); //�������� ��������� �� ��������� ������� ������
	Node* tmp_node = (Node*)malloc(sizeof(Node)); // ������� ����� ����
	tmp_node->vertex = data;
	tmp_node->next = NULL;
	last->next = tmp_node; //���������� � ��������� ������� ������ ��������� �� ����� ����
}

void createLinkedList(int** a, Node** head, int n) //������� ������� ������
{
	for (int i = 0; i < n; i++)
	{
		add_Node_to_beginning(&head[i], i); //�������� ����� ������� � �� �����
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1)
			{
				add_Node_to_end(head[i], j); //��������� � ������� ������� � ��� �������
			}
		}
	}
}


void printLinkedList(const Node* head) {
	cout << endl;
	while (head) {
		cout << head->vertex + 1 << " -> ";
		head = head->next;
	}
	cout << endl;
}

void DFS(int** a, bool* visited, int n, int v) //����� � �������, v - ������� �������, n - ���-�� ������, a - ������
{
	cout <<  v + 1 << " ";
	visited[v] = true; //�������� ������� �������
	for (int i = 0; i < n; i++)
	{
		if (a[v][i] == 1 && visited[i] == false) //��������� ������� � ��� �������
		{
			DFS(a, visited, n, i); //�������� ��������
		}
	}

}


void DFSlist(Node** head, bool* visited, int v)
{
	cout <<  v + 1 << " --> ";
	visited[v] = true;
	Node* tmp_node = head[v];
	while (tmp_node) //���� �� ������� �������
	{
		if (visited[tmp_node->vertex] == false)
			DFSlist(head, visited, tmp_node->vertex); //���� ������� �� �������� �� �������� �� ����� � ����� � ���� ������ �� ���
		tmp_node = tmp_node->next;
	}
}

void DFS_no_rec(int** a, bool* visited, int n, int v) { //����� ����� ��� ��������
	stack <int> stack;
	stack.push(v);
	while (!stack.empty())
	{
		if (visited[stack.top()] == false)
		{
			visited[stack.top()] = true;
			cout << stack.top() + 1;
			v = stack.top();
			stack.pop();
			for (int i = n - 1; i > 0; i--)
			{
				if (a[v][i] == 1 && visited[i] == false)
				{
					stack.push(i);
				}
			}
		}
		else
		{
			stack.pop();
		}
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	stack <int> stack;
	int** a, N, num; //N-���-�� ������, num-������� ��� �����
	cout << "������� ������ �������: ";
	cin >> N;
	Node** head = (Node**)malloc(N * sizeof(Node*));
	for (int i = 0; i < N; i++) {
		head[i] = NULL;
	}

	bool* visited = (bool*)malloc(N * sizeof(bool));
	for (int i = 0; i < N; i++)
	{
		visited[i] = false;
	}

	a = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		a[i] = (int*)malloc(N * sizeof(int));
	}

	for (int i = 0; i < N; i++)
	{
		a[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			a[i][j] = rand() % 2;
			a[j][i] = a[i][j];


		}
	}

	cout << "\n ����� ������� ���������\n ";

	cout << endl;
	cout << "\t";
	for (int i = 0; i < N; i++) { // ����� ������ ���������

		cout << endl;

		for (int j = 0; j < N; j++) {
			cout << a[i][j] << " ";
		}


	}

	cout << "\n������� ������� ��� ������ ������ ����� � ������� : ";
	cin >> num;
	num--;


	cout << "\n\n����������� ������ � ������� �� ������� ��������� : ";
		DFS(a, visited, N, num);
		cout << endl;

	for (int i = 0; i < N; i++)
		visited[i] = false;

	createLinkedList(a, head, N);
	cout << "\n�������� ������ ���������: ";
	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);

	cout << "\n����������� ������ � ������� �� ������ ��������� : ";
	DFSlist(head, visited, num);
	cout << endl;

	for (int i = 0; i < N; i++) {
		visited[i] = false;
	}

	cout << "\n������ � ������� �� ������� ��������� ��� ����������� �������: ";
	DFS_no_rec(a, visited, N, num);
	cout << endl << endl;
	_getch;
}

