#pragma once

//�̵� ����
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define NONE 4

//Color
#define BLACK 10
#define WHITE 11
#define BLUE 12
#define RED 13
#define PURPLE 14
#define YELLOW 15


//��ǥ
class coordinate
{
public:
	int x;
	int y;
};

//�̷� ��
class Node
{
public:
	bool visit;            //�湮�ߴ����� ����
	bool wall[4];          //��
	int back;             //Solving���� �������� ���� ����

	Node();
	Node(int value, int x, int y);
	~Node();

};

//Stack�� ���
class Stack_node
{
public:
	coordinate position;   //�� ��ġ

	Stack_node* pNext;     //���� ���

	Stack_node();
	Stack_node(coordinate pos);
	~Stack_node();
};

class Stack
{
public:
	Stack_node* pHead;   //ù ���
	int num;         //����� ��

	Stack();
	~Stack();

	void push(coordinate pos);   //�߰�
	coordinate pop();                    //����
	bool isEmpty();             //����ִ��� �Ǵ��ϴ� �Լ�
};


class Queue_node
{
public:
	coordinate position;   //�� ��ġ

	Queue_node* pNext;    //���� ���

	Queue_node();
	Queue_node(coordinate pos);
	~Queue_node();
};

class Queue
{
public:
	Queue_node* pHead;   //ù ���
	Queue_node* pTail;    //������ ���
	int num;         //����� ��

	Queue();
	~Queue();

	void push(coordinate pos);  //�߰�
	coordinate pop();                //����
	bool isEmpty();             //����ִ��� �Ǵ��ϴ� �Լ�
};

class MAZE
{
public:
	Node** maze;                        //�̷� 2���� �迭

	int row;           //��
	int col;            //��

	MAZE(int row, int col);
	~MAZE();
};


