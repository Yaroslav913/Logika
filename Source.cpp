#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <iostream>
#include <locale.h>
#include <malloc.h>

using namespace std;

int** mas1, ** mas2, ** m_longed, ** mas3;
int N;

typedef struct Node {
	char vertex;
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

void cleanlist(Node** head, int n)
{
	for (int i = 0; i < n; i++)
		head[i] = NULL;
}

void cleanlistfield(Node** head, int del, int n)
{
	Node* tmp;
	int back;
	for (int i = 0; i < n; i++)
	{
		tmp = head[i];
		while (tmp)
		{
			if (tmp->next)
				if (tmp->next->vertex == del)
				{
					tmp->next = tmp->next->next;
				}
			if (tmp->vertex >= del)
			{
				back = tmp->vertex;
				back--;
				tmp->vertex = back;
			}
			tmp = tmp->next;
		}
	}

	for (int i = del; i < n - 1; i++)
	{
		head[i] = head[i + 1];
	}
	head[n - 1] = NULL;
}

void paste(Node* head, int m)
{
	Node* tmp;
	tmp = (Node*)malloc(sizeof(Node));
	tmp->vertex = m;
	tmp->next = head->next;
	head->next = tmp;
}

void addver(Node** head, int field, int n)
{
	Node* ptr, * tmp;
	int base = head[field]->vertex, search;
	tmp = head[field];
	tmp = tmp->next;
	while (tmp)
	{
		search = tmp->vertex;
		for (int i = 0; i < n - 1; i++)
		{
			if (head[i]->vertex == search)
			{
				if (!head[i]->next)
				{
					add_Node_to_beginning(&head[i], base);
				}
				ptr = head[i];
				while (ptr->next)
				{
					if (ptr->next->vertex == base)
					{
						break;
					}
					if (ptr->next->vertex > base)
					{
						paste(ptr, base);
					}
				}
				break;
			}
		}
		tmp = tmp->next;
	}
}



void printLinkedList(Node* head) {
	cout << endl;
	while (head) {
		printf("%d �>", head->vertex + 1);
		head = head->next;
	}
	cout << endl;
}

void identificationlist(int v1, int v2, Node** head, int n)
{
	int del, field;
	Node* ptr = NULL, * tmp;
	if (v1 > v2)
	{
		del = v1 - 1;
		field = v2 - 1;
	}
	else
	{
		del = v2 - 1;
		field = v1 - 1;
	}
	tmp = head[del]->next;
	ptr = (Node*)malloc(sizeof(Node));
	ptr->vertex = head[field]->vertex;
	ptr->next = NULL;
	head[field] =
		head[field]->next;
	while (head[field] || tmp)
	{
		if (head[field] && tmp)
		{
			if (head[field]->vertex > tmp->vertex)
			{
				add_Node_to_end(ptr, tmp->vertex);
				tmp = tmp->next;
				continue;
			}
			if (head[field]->vertex < tmp->vertex)
			{
				add_Node_to_end(ptr, head[field]->vertex);
				head[field] = head[field]->next;
				continue;
			}
			if (head[field]->vertex == tmp->vertex)
			{
				add_Node_to_end(ptr, tmp->vertex);
				tmp = tmp->next;
				head[field] = head[field]->next;
				continue;
			}
		}
		if (head[field])
		{
			while (head[field])
			{
				add_Node_to_end(ptr, head[field]->vertex);
				head[field] = head[field]->next;
			}
		}
		else
		{
			while (tmp)
			{
				add_Node_to_end(ptr, tmp->vertex);
				tmp = tmp->next;
			}
		}
	}
	head[field] = ptr;
	fflush(stdin);
	cleanlistfield(head, del, n);
	addver(head, field, n);
}

void identificationlist_2(int v1, int v2, Node** head, int n)
{
	int del, field;
	Node* ptr = NULL, * tmp;
	if (v1 > v2)
	{
		del = v1 - 1;
		field = v2 - 1;
	}
	else
	{
		del = v2 - 1;
		field = v1 - 1;
	}
	tmp = head[del]->next;
	ptr = (Node*)malloc(sizeof(Node));
	ptr->vertex = head[field]->vertex;
	ptr->next = NULL;
	head[field] = head[field]->next;
	while (head[field] || tmp)
	{
		if (head[field] && tmp)
		{
			if (head[field]->vertex > tmp->vertex)
			{
				add_Node_to_end(ptr, tmp->vertex);
				tmp = tmp->next;
				continue;
			}
			if (head[field]->vertex < tmp->vertex)
			{
				add_Node_to_end(ptr, head[field]->vertex);
				head[field] = head[field]->next;
				continue;
			}
			if (head[field]->vertex == tmp->vertex)
			{
				add_Node_to_end(ptr, tmp->vertex);
				tmp = tmp->next;
				head[field] = head[field]->next;
				continue;
			}
		}
		if (head[field])
		{
			while (head[field])
			{
				add_Node_to_end(ptr, head[field]->vertex);
				head[field] = head[field]->next;
			}
		}
		else
		{
			while (tmp)
			{
				add_Node_to_end(ptr, tmp->vertex);
				tmp = tmp->next;
			}
		}
	}
	head[field] = ptr;
	fflush(stdin);
	cleanlistfield(head, del, n);
}

void splitinglist(Node** head, int v, int n)
{
	add_Node_to_beginning(&head[n - 1], n - 1);
	Node* ptr = head[v];
	if (ptr->next)
	{
		if (ptr->vertex < ptr->next->vertex)
		{
			add_Node_to_end(head[n - 1], ptr->vertex);
			add_Node_to_end(head[n - 1], ptr->next->vertex);
			ptr->next = ptr->next->next;
		}
		else
		{
			add_Node_to_end(head[n - 1], ptr->next->vertex);
			add_Node_to_end(head[n - 1], ptr->vertex);
			ptr->next = ptr->next->next;
		}
	}
	else
	{
		add_Node_to_end(head[n], ptr->vertex);
	}
}


void main() {

	setlocale(LC_ALL, "russian");

	cout << "\n ������� ������ �������: ";
	cin >> N;

	Node** head = (Node**)malloc(N * sizeof(Node*));
	for (int i = 0; i < N; i++)
		head[i] = NULL;


	mas1 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		mas1[i] = (int*)malloc(N * sizeof(int));
	}

	mas2 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		mas2[i] = (int*)malloc(N * sizeof(int));
	}


	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		mas1[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			mas1[i][j] = rand() % 2;
			mas1[j][i] = mas1[i][j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		mas2[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			mas2[i][j] = rand() % 2;
			mas2[j][i] = mas2[i][j];


		}
	}


	printf("\n 1. ����� ��������������� ������ ��������� ����������������� ������ \n");

	for (int i = 0; i < N; i++) {

		cout << endl;

		for (int j = 0; j < N; j++) {
			cout << mas1[i][j] << " ";
		}


	}

	cout << endl;

	for (int i = 0; i < N; i++) {

		cout << endl;

		for (int j = 0; j < N; j++) {
			cout << mas2[i][j] << " ";
		}


	}


	createLinkedList(mas1, head, N);
	cout << "\n\n������ ��������� ����� �:" << endl;;

	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);
	cleanlist(head, N);
	cout << endl << endl;
	createLinkedList(mas2, head, N);
	cout << "\n\n������ ��������� ����� B:\n";

	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);
	cleanlist(head, N);
	cout << endl << endl;


	m_longed = (int**)malloc((N + 1) * sizeof(int*)); printf("\t");
	for (int i = 0; i < (N + 1); i++)
	{
		m_longed[i] = (int*)malloc((N + 1) * sizeof(int));
	}


	int v1, v2;
	createLinkedList(mas2, head, N);
	cout << "\n\n 2. ����� ������� ������ ������� ������������?\n" << " ";
	cin >> v1 >> v2;

	int del, not_del;

	int i1 = 0, j = 0, j1 = 1, sch = 0;


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			m_longed[i][j] = mas2[i][j];
		}
	}


	if (v1 > v2)

	{

		del = v1 - 1;

		not_del = v2 - 1;

	}

	else

	{

		del = v2 - 1;

		not_del = v1 - 1;

	}

	for (int i = 0; i < N; i++)

	{

		if (m_longed[del][i] == 1)

			m_longed[not_del][i] = 1;

		if (m_longed[i][del] == 1)

			m_longed[i][not_del] = 1;

	}

	for (int i = 0; i < N; i++)

	{

		for (int j = del; j < N - 1; j++)

		{

			m_longed[i][j] = m_longed[i][j + 1];

		}

	}

	for (int i = del; i < N - 1; i++)

	{

		for (int j = 0; j < N; j++)

		{

			m_longed[i][j] = m_longed[i + 1][j];

		}

	}

	if (mas2[del][not_del]) {
		m_longed[not_del][not_del] = 1;
	}

	for (int i = 0; i < (N - 1); i++)
	{

		cout << endl;

		for (int j = 0; j < (N - 1); j++)
		{
			cout << m_longed[i][j];
		}

	}

	identificationlist(v1, v2, head, N);

	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);
	cleanlist(head, N);
	cout << endl << endl;

	createLinkedList(mas2, head, N);

	cout << "\n\n 2. ����� ����� ������ ������� �������?\n" << " ";
	cin >> v1 >> v2;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			m_longed[i][j] = mas2[i][j];
		}
	}


	if (v1 > v2)

	{

		del = v1 - 1;

		not_del = v2 - 1;

	}

	else

	{

		del = v2 - 1;

		not_del = v1 - 1;

	}

	for (int i = 0; i < N; i++)

	{

		if (m_longed[del][i] == 1)

			m_longed[not_del][i] = 1;

		if (m_longed[i][del] == 1)

			m_longed[i][not_del] = 1;

	}

	for (int i = 0; i < N; i++)

	{

		for (int j = del; j < N - 1; j++)

		{

			m_longed[i][j] = m_longed[i][j + 1];

		}

	}

	for (int i = del; i < N - 1; i++)

	{

		for (int j = 0; j < N; j++)

		{

			m_longed[i][j] = m_longed[i + 1][j];

		}

	}

	m_longed[not_del][not_del] = 0;


	for (int i = 0; i < (N - 1); i++)
	{

		cout << endl;

		for (int j = 0; j < (N - 1); j++)
		{
			cout << m_longed[i][j];
		}

	}

	int N2 = N + 1;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			m_longed[i][j] = mas2[i][j];
		}
	}

	for (int i = 0; i < N2; i++)
	{
		for (int j = 0; j < N2; j++)
		{
			if (m_longed[i][j] < 0 || m_longed[i][j] > 1)
				m_longed[i][j] = 0;
		}
	}

	identificationlist_2(v1, v2, head, N);

	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);
	cleanlist(head, N);


	cout << "\n\n 2. ����� ������� ������ ������� ���������?\n" << " ";
	cin >> v1;

	v1 = v1 - 1;
	int i = v1;
	for (; i < N2; i++)
	{
		if (m_longed[v1][i] == 1)
		{
			m_longed[N2 - 1][i] = m_longed[i][N2 - 1] = 1;

		}
		else
			m_longed[N2 - 1][i] = m_longed[i][N2 - 1] = 0;
	}


	m_longed[N2 - 1][v1] = m_longed[v1][N2 - 1] = 1;

	for (int i = 0; i < N2; i++)
	{

		cout << endl;

		for (int j = 0; j < N2; j++)
		{
			cout << m_longed[i][j];
		}

	}

	cleanlist(head, N + 1);
	createLinkedList(m_longed, head, N + 1);

	for (int i = 0; i < N + 1; i++)
		printLinkedList(head[i]);
	cleanlist(head, N);


	cout << "\n\n 3. ����������� ������ 1 � 2\n";

	for (int i = 0; i < N; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
		{
			m_longed[i][j] = mas1[i][j] || mas2[i][j];
			cout << m_longed[i][j];
		}
	}

	cout << "\n\n 3. ����������� ������ 1 � 2\n";

	for (int i = 0; i < N; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
		{
			m_longed[i][j] = mas1[i][j] & mas2[i][j];
			cout << m_longed[i][j];
		}
	}

	cout << "\n\n 3. ��������� ����� ������ 1 � 2\n";

	for (int i = 0; i < N; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
		{
			m_longed[i][j] = mas1[i][j] ^ mas2[i][j];
			cout << m_longed[i][j];
		}
	}

	cout << "\n\n��������� ������������ A � B";
	mas3 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < (N * N); i++)
	{
		mas3[i] = (int*)malloc((N * N) * sizeof(int));
	}
	int a1, a2;
	for (int i = 0; i < N; i++)
	{
		for (int m = 0; m < N; m++)
		{
			cout << endl << endl;
			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{

					if (i == j) {
						mas3[i][j] = mas2[m][k];
					}
					if (m == k)
					{
						mas3[i][j] = mas1[i][j];
					}
					if ((i != j) && (m != k))
					{
						mas3[i][j] = 0;
					}

				}
			}
		}
	}
	cout << endl;
	for (i = 0; i < N * N; i++)
	{
		for (j = 0; j < N * N; j++)
		{
			cout << mas3[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;



	_getch();

}