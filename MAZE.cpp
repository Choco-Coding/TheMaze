#include "pch.h"
#include "MAZE.h"

Node::Node()
{
	//초기화
	for (int i = 0; i < 4; i++)
	{
		wall[i] = true;     //벽이 모두 있는 것으로 초기화
	}

	visit = false;    //방문하지 않은 것으로 초기화
}

Node::Node(int value, int x, int y)
{
	//초기화
	for (int i = 0; i < 4; i++)
	{
		wall[i] = true;   //벽이 모두 있는 것으로 초기화
	}

	visit = false;
}

Node::~Node()
{
	visit = false;
}



Stack_node::Stack_node()
{

	//초기화
	this->position.x = 0;
	this->position.y = 0;
	this->pNext = nullptr;
}

Stack_node::Stack_node(coordinate pos)
{
	//전달 받은 값으로 초기화
	this->position = pos;
	this->pNext = nullptr;
}

Stack_node::~Stack_node()
{
	pNext = nullptr;
}


Stack::Stack()
{
	//초기화
	pHead = nullptr;
	num = 0;
}

Stack::~Stack()
{
	Stack_node* pPre;

	//할당된 메모리 모두 해제
	while (pHead != nullptr)
	{
		pPre = pHead;
		pHead = pHead->pNext;     //다음 노드로 이동
		delete pPre;
	}
}

void Stack::push(coordinate pos)
{
	Stack_node* pNew = new Stack_node(pos);  //노드 생성

	
	if (pHead == nullptr)
	{
		pHead = pNew;  //첫 노드로 추가
	}
	else
	{
		//첫 노드 앞에 추가
		pNew->pNext = pHead;
		pHead = pNew;
	}
	num++;
}

coordinate Stack::pop()
{
	if (num > 0)
	{
		coordinate pos = pHead->position;   //좌표 정보 저장
		Stack_node* pPre = pHead;

		pHead = pHead->pNext;

		delete pPre;   //메모리 해제
		num--;
		return pos;   //좌표 반환
	}
	else
	{
		//반환할 노드가 없을 경우
		return { -1, -1 };
	}

}

bool Stack::isEmpty()
{
	if (num == 0)
	{
		return true;   //비어 있으면 true 반환
	}
	else
	{
		return false;
	}
}

Queue_node::Queue_node()
{
	//초기화
	this->position.x = 0;
	this->position.y = 0;
	this->pNext = nullptr;

}

Queue_node::Queue_node(coordinate pos)
{
	//전달 받은 값으로 초기화
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
	//할당된 메모리 해제
	while (pHead != nullptr)
	{
		pPre = pHead;
		pHead = pHead->pNext;   //다음 노드로 이동
		delete pPre;
	}
}

void Queue::push(coordinate pos)
{
	//새로운 노드 할당
	Queue_node* pNew = new Queue_node(pos);

	if (pHead == nullptr)
	{
		//노드를 처음 추가할 경우
		pHead = pNew;
		pTail = pNew;
	}
	else
	{
		//마지막 노드 다음에 추가
		pTail->pNext = pNew;
		pTail = pNew;
	}
	num++;
}

coordinate Queue::pop()
{
	//가장 앞의 노드에 저장된 좌표 값을 반환한다.
	if (num > 0)
	{
		coordinate pos = pHead->position;  //좌표 값 저장
		Queue_node* pPre = pHead;

		pHead = pHead->pNext;         //다음 노드로 이동

		delete pPre;
		num--;
		return pos;            //미로에서의 좌표 반환
	}
	else
	{
		return { -1, -1 };  //반환할 노드가 없는 경우
	}
}

bool Queue::isEmpty()
{
	if (num == 0)
	{
		return true;    //Queue가 비어 있는 경우 true 반환
	}
	else
	{
		return false;
	}
}



//미로 class 생성자
MAZE::MAZE(int row, int col)
{
	this->row = row;
	this->col = col;
	//2차원 배열 동적 할당
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

//미로 파괴자 (할당된 메모리 해제)
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
