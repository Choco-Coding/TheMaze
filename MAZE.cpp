#include "pch.h"
#include "MAZE.h"

Node::Node()
{
	//�ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		wall[i] = true;     //���� ��� �ִ� ������ �ʱ�ȭ
	}

	visit = false;    //�湮���� ���� ������ �ʱ�ȭ
}

Node::Node(int value, int x, int y)
{
	//�ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		wall[i] = true;   //���� ��� �ִ� ������ �ʱ�ȭ
	}

	visit = false;
}

Node::~Node()
{
	visit = false;
}



Stack_node::Stack_node()
{

	//�ʱ�ȭ
	this->position.x = 0;
	this->position.y = 0;
	this->pNext = nullptr;
}

Stack_node::Stack_node(coordinate pos)
{
	//���� ���� ������ �ʱ�ȭ
	this->position = pos;
	this->pNext = nullptr;
}

Stack_node::~Stack_node()
{
	pNext = nullptr;
}


Stack::Stack()
{
	//�ʱ�ȭ
	pHead = nullptr;
	num = 0;
}

Stack::~Stack()
{
	Stack_node* pPre;

	//�Ҵ�� �޸� ��� ����
	while (pHead != nullptr)
	{
		pPre = pHead;
		pHead = pHead->pNext;     //���� ���� �̵�
		delete pPre;
	}
}

void Stack::push(coordinate pos)
{
	Stack_node* pNew = new Stack_node(pos);  //��� ����

	
	if (pHead == nullptr)
	{
		pHead = pNew;  //ù ���� �߰�
	}
	else
	{
		//ù ��� �տ� �߰�
		pNew->pNext = pHead;
		pHead = pNew;
	}
	num++;
}

coordinate Stack::pop()
{
	if (num > 0)
	{
		coordinate pos = pHead->position;   //��ǥ ���� ����
		Stack_node* pPre = pHead;

		pHead = pHead->pNext;

		delete pPre;   //�޸� ����
		num--;
		return pos;   //��ǥ ��ȯ
	}
	else
	{
		//��ȯ�� ��尡 ���� ���
		return { -1, -1 };
	}

}

bool Stack::isEmpty()
{
	if (num == 0)
	{
		return true;   //��� ������ true ��ȯ
	}
	else
	{
		return false;
	}
}

Queue_node::Queue_node()
{
	//�ʱ�ȭ
	this->position.x = 0;
	this->position.y = 0;
	this->pNext = nullptr;

}

Queue_node::Queue_node(coordinate pos)
{
	//���� ���� ������ �ʱ�ȭ
	this->position = pos;
	this->pNext = nullptr;
}

Queue_node::~Queue_node()
{
	pNext = nullptr;
}


Queue::Queue()
{
	pHead = nullptr;
	pTail = nullptr;
	num = 0;
}

Queue::~Queue()
{
	Queue_node* pPre;
	pTail = nullptr;
	//�Ҵ�� �޸� ����
	while (pHead != nullptr)
	{
		pPre = pHead;
		pHead = pHead->pNext;   //���� ���� �̵�
		delete pPre;
	}
}

void Queue::push(coordinate pos)
{
	//���ο� ��� �Ҵ�
	Queue_node* pNew = new Queue_node(pos);

	if (pHead == nullptr)
	{
		//��带 ó�� �߰��� ���
		pHead = pNew;
		pTail = pNew;
	}
	else
	{
		//������ ��� ������ �߰�
		pTail->pNext = pNew;
		pTail = pNew;
	}
	num++;
}

coordinate Queue::pop()
{
	//���� ���� ��忡 ����� ��ǥ ���� ��ȯ�Ѵ�.
	if (num > 0)
	{
		coordinate pos = pHead->position;  //��ǥ �� ����
		Queue_node* pPre = pHead;

		pHead = pHead->pNext;         //���� ���� �̵�

		delete pPre;
		num--;
		return pos;            //�̷ο����� ��ǥ ��ȯ
	}
	else
	{
		return { -1, -1 };  //��ȯ�� ��尡 ���� ���
	}
}

bool Queue::isEmpty()
{
	if (num == 0)
	{
		return true;    //Queue�� ��� �ִ� ��� true ��ȯ
	}
	else
	{
		return false;
	}
}



//�̷� class ������
MAZE::MAZE(int row, int col)
{
	this->row = row;
	this->col = col;
	//2���� �迭 ���� �Ҵ�
	maze = new Node * [row];
	if (maze == nullptr)
	{
		exit(100);
	}

	maze[0] = new Node[row * col];
	if (maze[0] == nullptr)
	{
		delete maze;
		exit(101);
	}

	for (int i = 1; i < row; i++)
	{
		maze[i] = maze[i - 1] + col;
	}
}

//�̷� �ı��� (�Ҵ�� �޸� ����)
MAZE::~MAZE()
{
	if (maze != nullptr)
	{
		if (maze[0] != nullptr)
		{
			delete[] maze[0];
		}

		delete[] maze;
	}
}
