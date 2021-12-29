
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <locale.h>
#include <queue>
#include <ctime>
#include <chrono>

using namespace std;

class Timer

{

private:

	using clock_t = std::chrono::high_resolution_clock;

	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:

	Timer() : m_beg(clock_t::now())

	{

	}

	void reset()

	{

		m_beg = clock_t::now();

	}

	double elapsed() const

	{

		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();

	}

};

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

int delete_node(Node** head) { //������� ���� �� ������� ��������� �����
	Node* prev = NULL;
	int val;
	prev = (*head); //�������� �� ��������� ���������� prev �����
	val = prev->vertex;
	(*head) = (*head)->next; //� head ������ ����� ���������� ����
	free(prev); //������� ��������� ���������� prev
	return val;
}


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

void createLinkedList(int** mas, Node** head, int N) //������� ������� ������
{
	for (int i = 0; i < N; i++)
	{
		add_Node_to_beginning(&head[i], i); //�������� ����� ������� � �� �����
		for (int j = 0; j < N; j++)
		{
			if (mas[i][j] == 1)
			{
				add_Node_to_end(head[i], j); //��������� � ������� ������� � ��� �������
			}
		}
	}
}


void printLinkedList(Node* head) {
	cout << endl;
	while (head) {
		cout << head->vertex + 1 << " -> ";
		head = head->next;
	}
	cout << endl;
}

void BFS(int** mas, bool* visited, int N, int v) //N - ����� ������, v - �������, � ������� �������� �����
{
	queue<int> queue;
	queue.push(v);
	visited[v] = true;
	while (!queue.empty())
	{
		v = queue.front();
		queue.pop();
		cout << v + 1 << " ";
		for (int i = 0; i < N; i++)
		{
			if (mas[v][i] == 1 && visited[i] == false)
			{
				queue.push(i);
				visited[i] = true;
			}
		}
	}
}


void BFS_ForLinkedList(Node** head, bool* visited, int v)
{
	Node** tmp_node = head; //�������� �����, �������� ������ �����
	queue <int> queue;
	queue.push(tmp_node[v]->vertex);
	visited[tmp_node[v]->vertex] = true;
	while (!queue.empty())
	{
		v = queue.front();
		queue.pop();
		cout << v + 1 << " ";
		while (tmp_node[v])
		{
			if (visited[tmp_node[v]->vertex] == false)
			{
				queue.push(tmp_node[v]->vertex);
				visited[tmp_node[v]->vertex] = true;
			}
			tmp_node[v] = tmp_node[v]->next; //������� � ���������� ���� � ������
		}
	}
}

void BFS_linkedlist_as_queue(int** mas, bool* visited, int v, int N)
{
	Node* head = NULL;
	add_Node_to_beginning(&head, v); //��������� ���� � ������ �������� � ������
	visited[v] = true;
	while (head) //���� ���� ���� ���� ��������
	{
		v = delete_node(&head); //������� ������� (�� �������� �������)
		cout << v + 1 << " ";
		for (int i = 0; i < N; i++)
		{
			if (mas[v][i] == 1 && visited[i] == false)
			{
				if (head == NULL)
				{
					add_Node_to_beginning(&head, i); //���� ��� "������" ��������� ������� ������� ��� ������
				}
				else
				{
					add_Node_to_end(head, i);
					//����� ��������� � ��� ��������� ������� �������
				}
				visited[i] = true;
			}
		}
	}
}


void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	queue <int> queue;
	int** mas, N, num;
	time_t start, end;
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
	mas = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		mas[i] = (int*)malloc(N * sizeof(int));
	}
	for (int i = 0; i < N; i++)
	{
		mas[i][i] = 0;
		for (int j = i + 1; j < N; j++)
		{
			mas[i][j] = rand() % 2;
			mas[j][i] = mas[i][j];
		}
	}
	cout << "\n����� ������� ���������\n ";
	cout << endl;
	cout << "\t";
	
	for (int i = 0; i < N; i++) { // ����� ������ ���������

		cout << endl;

		for (int j = 0; j < N; j++) {
			cout << mas[i][j] << " ";
		}
	}
	bool bt = false;
	while (bt == false)
	{
		cout << "\n\n������� ������� ��� ������ ������ ����� � ������ : ";
		cin >> num;
		num--;
		if (num > N)
		{
			cout << "������, ��������� ����� ����)))";
		}
		else
		{
			bt = true;
		}
	}

	cout << "\n������ � ������ �� ������� ��������� : ";
	time(&start);
	Timer t;
	BFS(mas, visited, N, num);
	time(&end);
	cout << "\n\n����� �� ������ � ������ " << t.elapsed() << endl;
	for (int i = 0; i < N; i++)
		visited[i] = false;
	createLinkedList(mas, head, N);
	cout << "\n�������� ������ ���������: ";
	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);
	cout << "\n������ � ������ �� ������ ��������� : ";
	Timer t1;
	BFS_ForLinkedList(head, visited, num);
	cout << "\n\n����� �� ������ �� ������ ��������� " << t1.elapsed() << endl;
	for (int i = 0; i < N; i++)
		visited[i] = false;
	cout << "\n������ � ������ �� ������� ��������� c �������������� �������, ����������� �� ������ ���������: ";
	Timer t2;
	BFS_linkedlist_as_queue(mas, visited, num, N);
	cout << "\n\n����� �� ������ �� ������� ��������� � �������������� �������, ����������� �� ������ ��������� " << t2.elapsed() << endl;
	cout << endl << endl;
	_getch();
}