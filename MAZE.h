#pragma once

//이동 방향
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


//좌표
class coordinate
{
public:
	int x;
	int y;
};

//미로 방
class Node
{
public:
	bool visit;            //방문했는지의 여부
	bool wall[4];          //벽
	int back;             //Solving에서 역추적에 사용될 방향

	Node();
	Node(int value, int x, int y);
	~Node();

};

//Stack의 노드
class Stack_node
{
public:
	coordinate position;   //방 위치

	Stack_node* pNext;     //다음 노드

	Stack_node();
	Stack_node(coordinate pos);
	~Stack_node();
};

class Stack
{
public:
	Stack_node* pHead;   //첫 노드
	int num;         //노드의 수

	Stack();
	~Stack();

	void push(coordinate pos);   //추가
	coordinate pop();                    //삭제
	bool isEmpty();             //비어있는지 판단하는 함수
};


class Queue_node
{
public:
	coordinate position;   //방 위치

	Queue_node* pNext;    //다음 노드

	Queue_node();
	Queue_node(coordinate pos);
	~Queue_node();
};

class Queue
{
public:
	Queue_node* pHead;   //첫 노드
	Queue_node* pTail;    //마지막 노드
	int num;         //노드의 수

	Queue();
	~Queue();

	void push(coordinate pos);  //추가
	coordinate pop();                //삭제
	bool isEmpty();             //비어있는지 판단하는 함수
};

class MAZE
{
public:
	Node** maze;                        //미로 2차원 배열

	int row;           //행
	int col;            //열

	MAZE(int row, int col);
	~MAZE();
};


