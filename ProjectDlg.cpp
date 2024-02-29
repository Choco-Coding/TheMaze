
// ProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project.h"
#include "ProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjectDlg 대화 상자



CProjectDlg::CProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Row_Input, m_Row);
	DDX_Control(pDX, Column_Input, m_Column);
	DDX_Control(pDX, IDC_STATIC_CANVAS, m_staticCanvas);
	DDX_Control(pDX, Check_G, m_Animation_G);
	DDX_Control(pDX, Cheak_S, m_Animation_S);
}

BEGIN_MESSAGE_MAP(CProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Generate_Button, &CProjectDlg::OnBnClickedButton_Generate)
	ON_BN_CLICKED(Solve_Button, &CProjectDlg::OnBnClickedButton_Solve)
	ON_BN_CLICKED(Exit_Button, &CProjectDlg::OnBnClickedButton_Exit)
	ON_CONTROL_RANGE(BN_CLICKED, DFS_Radio, BFS_Radio, &CProjectDlg::OnRadioGroup1Clicked)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CProjectDlg 메시지 처리기

BOOL CProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem(DFS_Radio))->SetCheck(TRUE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ProcessWindowMessage()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	}
}

//Generate 버튼
void CProjectDlg::OnBnClickedButton_Generate()
{
	//text editor로 입력한 row 값 불러오기
	CString RowInput;
	m_Row.GetWindowTextW(RowInput);
	row = _ttoi(RowInput);         //row에 저장
	m_staticCanvas.row = row;

	//text editor로 입력한 column 값 불러오기
	CString ColInput;
	m_Column.GetWindowTextW(ColInput);
	col = _ttoi(ColInput);          //col에 저장
	m_staticCanvas.col = col;

	//Generate
	if (row >= 4 && row <= 30 && col >= 4 && col <= 30)   //행과 열이 4 ~ 30일 경우 시행
	{
		if (m_staticCanvas.Maze != nullptr)
		{
			delete m_staticCanvas.Maze;    //이전 미로 삭제
		}

		m_staticCanvas.Maze = new MAZE(row, col);

		//커서 위치 초기화
		m_staticCanvas.current_row = -2;
		m_staticCanvas.current_col = -2;
		m_staticCanvas.L_Click_current_row = -2;
		m_staticCanvas.L_Click_current_col = -2;
		m_staticCanvas.R_Click_current_row = -2;
		m_staticCanvas.R_Click_current_col = -2;

		m_staticCanvas.pre_row = -1;
		m_staticCanvas.pre_col = -1;
		m_staticCanvas.L_Click_pre_row = -1;
		m_staticCanvas.L_Click_pre_col = -1;
		m_staticCanvas.R_Click_pre_row = -1;
		m_staticCanvas.R_Click_pre_col = -1;


		srand((unsigned int)time(NULL));

		m_staticCanvas.SetLength(row, col);       //미로의 크기 설정

		//미로의 탐색 위치
		coordinate POS = { rand() % col, rand() % row };   //미로를 생성할 랜덤 초기 위치 첨자 설정
		m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;

		Stack* stack = new Stack;
		int direction, fail;
		int record[4];                //중복된 랜덤 값이 나오지 않도록 기록
		int record_index;             //record 배열의 첨자
		bool delay = false;           //애니메이션 적용 때 미로의 마지막 방에서 delay 여부
		
		//DFS로 미로 생성 (stack이 비어있는 상태가 되면 종료)
		while (1)
		{
			fail = 0;       //주위의 방 중 방문했던 방의 수 (4가 되면 주위의 모든 방 방문한 것이다.)
			record_index = 0;

		retry:
			if (fail >= 4)
			{
				//주위의 모든 방 방문했을 경우 가장 최근의 방문한 방으로 돌아가기
				if (stack->isEmpty())
				{
					//stack이 비어있을 경우 DFS 종료
					fail = 0;
					break;
				}
				else
				{
					if (m_Animation_G.GetCheck())
					{
						//애니메이션 체크한 경우
						m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
						if (delay)
						{
							ProcessWindowMessage();
							Sleep(100);
						}
					}

					POS = stack->pop();    //stack에서 가장 최근의 방문한 방 위치 받기
					fail = 0;
					record_index = 0;
					delay = false;
				}
			}

			//이동 방향 랜덤으로 정하기
			//0 : UP, 1 : right, 2 : down, 3 : left
			while (1) {
				bool unique = true;     //일치하는 값의 존재 여부
				record[record_index] = rand() % 4;      //0 ~ 3 범위의 랜덤 값 생성

				//이전에 생성된 랜덤 값과 일치하는 것이 있는지 검사 -> 일치하는 값 있으면 다시 생성
				for (int i = 0; i < record_index; i++)
				{
					if (record[i] == record[record_index])
					{
						unique = false;      //일치하는 값이 있으면 false로 변경
					}
				}

				//일치하는 값이 없는 경우 해당 값을 선택하고 반복문 종료
				if (unique)
				{
					direction = record[record_index];
					record_index++;
					break;
				}
			}

			switch (direction)
			{
			case UP:
				if (POS.y - 1 >= 0)  //유효한 index인지 검사
				{
					if (m_staticCanvas.Maze->maze[POS.y - 1][POS.x].visit == false)  //방문했었는지 검사
					{
						stack->push(POS);   //기존 위치 추가

						//벽 삭제
						m_staticCanvas.Maze->maze[POS.y][POS.x].wall[UP] = false;
						m_staticCanvas.Maze->maze[POS.y - 1][POS.x].wall[DOWN] = false;


						if (m_Animation_G.GetCheck())
						{
							//애니메이션 체크한 경우
							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
							delay = true;
							ProcessWindowMessage();
							Sleep(100);
						}
						else
						{
							m_staticCanvas.GenerationMaze(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall);   //미로 그리기
						}

						POS.y--;   //이동
						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;
					}
					else
					{
						fail++;
						goto retry;
					}
				}
				else
				{
					fail++;
					goto retry;
				}
				break;


			case RIGHT:
				if (POS.x + 1 < col)  //유효한 index인지 검사
				{
					if (m_staticCanvas.Maze->maze[POS.y][POS.x + 1].visit == false)  //방문했었는지 검사
					{
						stack->push(POS);   //기존 위치 추가

						//벽 삭제
						m_staticCanvas.Maze->maze[POS.y][POS.x].wall[RIGHT] = false;
						m_staticCanvas.Maze->maze[POS.y][POS.x + 1].wall[LEFT] = false;

						if (m_Animation_G.GetCheck())
						{
							//애니메이션 체크한 경우
							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
							delay = true;
							ProcessWindowMessage();
							Sleep(100);
						}
						else
						{
							m_staticCanvas.GenerationMaze(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall);   //미로 그리기
						}

						POS.x++;   //이동
						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;
					}
					else
					{
						fail++;
						goto retry;
					}
				}
				else
				{
					fail++;
					goto retry;
				}
				break;

			case DOWN:
				if (POS.y + 1 < row)  //유효한 index인지 검사
				{
					if (m_staticCanvas.Maze->maze[POS.y + 1][POS.x].visit == false)  //방문했었는지 검사
					{
						stack->push(POS);   //기존 위치 추가

						//벽 삭제
						m_staticCanvas.Maze->maze[POS.y][POS.x].wall[DOWN] = false;
						m_staticCanvas.Maze->maze[POS.y + 1][POS.x].wall[UP] = false;

						if (m_Animation_G.GetCheck())
						{
							//애니메이션 체크한 경우
							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
							delay = true;
							ProcessWindowMessage();
							Sleep(100);

						}
						else
						{
							m_staticCanvas.GenerationMaze(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall);   //미로 그리기
						}

						POS.y++;   //이동
						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;
					}
					else
					{
						fail++;
						goto retry;
					}
				}
				else
				{
					fail++;
					goto retry;
				}
				break;

			case LEFT:
				if (POS.x - 1 >= 0)  //유효한 index인지 검사
				{
					if (m_staticCanvas.Maze->maze[POS.y][POS.x - 1].visit == false)  //방문했었는지 검사
					{
						stack->push(POS);   //기존 위치 추가

						//벽 삭제
						m_staticCanvas.Maze->maze[POS.y][POS.x].wall[LEFT] = false;
						m_staticCanvas.Maze->maze[POS.y][POS.x - 1].wall[RIGHT] = false;


						if (m_Animation_G.GetCheck())
						{
							
							//애니메이션 체크한 경우
							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
							delay = true;
							ProcessWindowMessage();
							Sleep(100);
						}
						else
						{
							m_staticCanvas.GenerationMaze(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall);   //미로 그리기
						}

						POS.x--;   //이동
						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;
					}
					else
					{
						fail++;
						goto retry;
					}
				}
				else
				{
					fail++;
					goto retry;
				}
				break;


			default:
				goto retry;
				break;
			}

		}

		delete stack;

		
		//애니메이션 체크한 경우 전체를 흰색 배경으로 다시 그리기
		if (m_Animation_G.GetCheck())
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					m_staticCanvas.GenerationMaze(i, j, m_staticCanvas.Maze->maze[i][j].wall);   //미로 그리기
				}
			}
		}
		
	}
	else
	{
		//행과 열이 범위를 벗어났을 경우 에러 처리
		CString error;
		error.Format(_T("ERROR:\n행과 열은 각각 4 이상, 30 이하이어야 합니다."));
		AfxMessageBox(error);        //에러 메시지 박스 출력
	}

	//모든 방의 visit을 다시 false로 초기화
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			m_staticCanvas.Maze->maze[i][k].visit = false;
		}
	}
}

//Solve 버튼
void CProjectDlg::OnBnClickedButton_Solve()
{
	
	//출발점의 미로 행, 열 설정
	int start_row = m_staticCanvas.L_Click_current_row;
	int start_col = m_staticCanvas.L_Click_current_col;

	//도착점의 미로 행, 열 설정
	int destination_row = m_staticCanvas.R_Click_current_row;
	int destination_col = m_staticCanvas.R_Click_current_col;

	
	if (start_row != -2 && start_col != -2 && destination_row != -2 && destination_col != -2)  //출발지, 도착지가 선택되었는지 검사
	{
		//전체를 흰색 배경으로 다시 그리기
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				m_staticCanvas.GenerationMaze(i, j, m_staticCanvas.Maze->maze[i][j].wall);   //미로 그리기

				//시작 위치일 경우 원 그리기
				if (i == start_row && j == start_col)
				{
					m_staticCanvas.draw_circle(i, j, RED);
				}

				//종료 위치일 경우 원 그리기
				if (i == destination_row && j == destination_col)
				{
					m_staticCanvas.draw_circle(i, j, BLUE);
				}
			}
		}

		//모든 방의 visit을 다시 false로 초기화
		for (int i = 0; i < row; i++)
		{
			for (int k = 0; k < col; k++)
			{
				m_staticCanvas.Maze->maze[i][k].visit = false;
			}
		}

		//미로에서의 위치 (시작 위치의 행과 열로 값 초기화)
		coordinate POS;
		POS.x = start_col;
		POS.y = start_row;

		m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;

		bool delay;           //애니메이션 적용 때 미로의 마지막 방에서 delay 여부

		Stack* stack;
		Queue* queue;

		switch (m_Radio)
		{
		case 0:
			//DFS 알고리즘으로 미로 풀이
			stack = new Stack;        //Stack 이용

			// 랜덤으로 탐색 방향을 정한다.

			int direction, fail;
			int record[4];                //중복된 랜덤 값이 나오지 않도록 기록
			int record_index;             //record 배열의 첨자
			delay = false;           //애니메이션 적용 때 미로의 마지막 방에서 delay 여부


			while (1)
			{
				fail = 0;       //주위의 방 중 방문했던 방의 수 (4가 되면 주위의 모든 방 방문한 것이다.)
				record_index = 0;

			retry:
				if (fail >= 4)
				{
					//더이상 이동할 방향이 없는 경우 가장 최근의 방문한 방으로 돌아가기
					if (stack->isEmpty())
					{
						//stack이 비어있을 경우 DFS 종료
						fail = 0;
						break;
					}
					else
					{
						if (m_Animation_S.GetCheck())
						{
							//애니메이션 체크한 경우
							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
							if (delay)
							{
								ProcessWindowMessage();
								Sleep(100);
							}
						}

						POS = stack->pop();    //stack에서 가장 최근의 방문한 방 위치 받기
						fail = 0;
						record_index = 0;
						delay = false;
					}
				}

				//도착점에 도착했을 경우 DFS 종료
				if (POS.x == destination_col && POS.y == destination_row)
				{
					m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
					break;
				}

				//이동 방향 랜덤으로 정하기
				//0 : UP, 1 : right, 2 : down, 3 : left
				while (1) {
					bool unique = true;     //일치하는 값의 존재 여부
					record[record_index] = rand() % 4;      //0 ~ 3 범위의 랜덤 값 생성

					//이전에 생성된 랜덤 값과 일치하는 것이 있는지 검사 -> 일치하는 값 있으면 다시 생성
					for (int i = 0; i < record_index; i++)
					{
						if (record[i] == record[record_index])
						{
							unique = false;      //일치하는 값이 있으면 false로 변경
						}
					}

					//일치하는 값이 없는 경우 해당 값을 선택하고 반복문 종료
					if (unique)
					{
						direction = record[record_index];
						record_index++;
						break;
					}
				}

				//UP, LEFT, RIGHT, DOWN 중 한 방향을 선택하여 이동
				//각각 3가지 조건(유효한 첨자, 방문한 적 없는 방, 벽이 없음)을 모두 만족해야 이동
				switch (direction)
				{
				case UP:
					if (POS.y - 1 >= 0)  //유효한 index인지 검사
					{
						if ((m_staticCanvas.Maze->maze[POS.y - 1][POS.x].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[UP] == false))  //방문했었는지, 벽이 없는지 검사
						{
							stack->push(POS);   //기존 방 위치 stack에 추가

							//애니메이션을 체크했을 경우 delay
							if (m_Animation_S.GetCheck())
							{
								ProcessWindowMessage();
								Sleep(100);
							}

							delay = true;

							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시

							POS.y--;    //위로 이동
							m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
							m_staticCanvas.Maze->maze[POS.y][POS.x].back = DOWN;    //역추적 경로 표시
						}
						else
						{
							fail++;
							goto retry;
						}
					}
					else
					{
						fail++;
						goto retry;
					}
					break;

				case RIGHT:
					if (POS.x + 1 < col)  //유효한 index인지 검사
					{
						if ((m_staticCanvas.Maze->maze[POS.y][POS.x + 1].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[RIGHT] == false))  //방문했었는지, 벽이 없는지 검사
						{
							stack->push(POS);   //기존 위치 추가

							//애니메이션을 체크했을 경우 delay
							if (m_Animation_S.GetCheck())
							{
								ProcessWindowMessage();
								Sleep(100);
							}

							delay = true;

							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시

							POS.x++;    //오른쪽으로 이동
							m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
							m_staticCanvas.Maze->maze[POS.y][POS.x].back = LEFT;    //역추적 경로 표시
						}
						else
						{
							fail++;
							goto retry;
						}
					}
					else
					{
						fail++;
						goto retry;
					}
					break;

				case DOWN:
					if (POS.y + 1 < row)  //유효한 index인지 검사
					{
						if ((m_staticCanvas.Maze->maze[POS.y + 1][POS.x].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[DOWN] == false))  //방문했었는지, 벽이 없는지 검사
						{
							stack->push(POS);   //기존 위치 추가

							//애니메이션을 체크했을 경우 delay
							if (m_Animation_S.GetCheck())
							{
								ProcessWindowMessage();
								Sleep(100);
							}

							delay = true;

							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시

							POS.y++;    //아래로 이동
							m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
							m_staticCanvas.Maze->maze[POS.y][POS.x].back = UP;    //역추적 경로 표시
						}
						else
						{
							fail++;
							goto retry;
						}
					}
					else
					{
						fail++;
						goto retry;
					}
					break;

				case LEFT:
					if (POS.x - 1 >= 0)  //유효한 index인지 검사
					{
						if ((m_staticCanvas.Maze->maze[POS.y][POS.x - 1].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[LEFT] == false))  //방문했었는지,  벽이 없는지 검사
						{
							stack->push(POS);   //기존 위치 추가

							//애니메이션을 체크했을 경우 delay
							if (m_Animation_S.GetCheck())
							{
								ProcessWindowMessage();
								Sleep(100);
							}

							delay = true;

							m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시

							POS.x--;    //왼쪽으로 이동
							m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
							m_staticCanvas.Maze->maze[POS.y][POS.x].back = RIGHT;    //역추적 경로 표시
						}
						else
						{
							fail++;
							goto retry;
						}
					}
					else
					{
						fail++;
						goto retry;
					}
					break;


				default:
					goto retry;
					break;
				}

			}

			delete stack;
			break;

		
		case 1:
			//BFS 알고리즘으로 미로 탐색
			queue = new Queue;              //Queue 이용

			m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);

			//방의 번호가 작은 것을 먼저 탐색한다.(오름차순)
			// -> 행이 작을 수록, 열이 작을 수록 우선 (UP -> LEFT -> RIGHT -> DOWN)
			while (1)
			{
				//도착점에 도착했을 경우 BFS 종료
				if (POS.x == destination_col && POS.y == destination_row)
				{
					m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);
					break;
				}

				//UP, LEFT, RIGHT, DOWN 중 방향을 선택하여 이동 (이동 가능한 모든 방 방문)
				//각각 3가지 조건(유효한 첨자, 방문한 적 없는 방, 벽이 없음)을 모두 만족해야 이동
				if (POS.y - 1 >= 0)	// UP
				{
					if ((m_staticCanvas.Maze->maze[POS.y - 1][POS.x].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[UP] == false))
					{
						//애니메이션을 체크했을 경우 delay
						if (m_Animation_S.GetCheck())
						{
							ProcessWindowMessage();
							Sleep(100);
						}



						POS.y--;
						queue->push(POS);    //새로운 방 위치 queue에 추가
						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //새로운 방에 방문했음을 표시
						m_staticCanvas.Maze->maze[POS.y][POS.x].back = DOWN;    //역추적 경로 표시
						m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시
						POS.y++;
					}
				}

				if (POS.x - 1 >= 0)  // LEFT
				{
					if ((m_staticCanvas.Maze->maze[POS.y][POS.x - 1].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[LEFT] == false))
					{
						//애니메이션을 체크했을 경우 delay
						if (m_Animation_S.GetCheck())
						{
							ProcessWindowMessage();
							Sleep(100);
						}


						POS.x--;
						queue->push(POS);    //새로운 방 위치 queue에 추가

						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
						m_staticCanvas.Maze->maze[POS.y][POS.x].back = RIGHT;    //역추적 경로 표시
						m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시
						POS.x++;
					}
				}

				if (POS.x + 1 < col)  // RIGHT
				{
					if ((m_staticCanvas.Maze->maze[POS.y][POS.x + 1].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[RIGHT] == false))
					{
						//애니메이션을 체크했을 경우 delay
						if (m_Animation_S.GetCheck())
						{
							ProcessWindowMessage();
							Sleep(100);
						}


						POS.x++;
						queue->push(POS);    //새로운 방 위치 queue에 추가

						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
						m_staticCanvas.Maze->maze[POS.y][POS.x].back = LEFT;    //역추적 경로 표시
						m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시
						POS.x--;
					}
				}

				if (POS.y + 1 < row)  // DOWN
				{
					if ((m_staticCanvas.Maze->maze[POS.y + 1][POS.x].visit == false) && (m_staticCanvas.Maze->maze[POS.y][POS.x].wall[DOWN] == false))
					{
						//애니메이션을 체크했을 경우 delay
						if (m_Animation_S.GetCheck())
						{
							ProcessWindowMessage();
							Sleep(100);
						}


						POS.y++;
						queue->push(POS);    //새로운 방 위치 queue에 추가

						m_staticCanvas.Maze->maze[POS.y][POS.x].visit = true;   //방문했음을 표시
						m_staticCanvas.Maze->maze[POS.y][POS.x].back = UP;    //역추적 경로 표시
						m_staticCanvas.paint_room(POS.y, POS.x, m_staticCanvas.Maze->maze[POS.y][POS.x].wall, PURPLE);   //탐색한 방 색칠하여 표시
						POS.y--;
					}
				}

				//이동할 수 있는 방이 없는 경우
				if (queue->isEmpty())
				{
					//queue가 모두 비어있는 상태가 되면 반복문 탈출
					break;
				}

				POS = queue->pop();     //queue로부터 다음 위치로 이동할 첨자 받기
			}
		

			delete queue;
			break;

		default:
			break;
		}
		

		//역추적하여 경로 그리기
		int back_row = destination_row;
		int back_col = destination_col;

		int current_direction;
		int pre_direction = NONE;

		while (1)
		{
			current_direction = m_staticCanvas.Maze->maze[back_row][back_col].back;  //back 방향 저장

			m_staticCanvas.paint_room(back_row, back_col, m_staticCanvas.Maze->maze[back_row][back_col].wall, PURPLE);   //탐색한 방 색칠하여 표시
			m_staticCanvas.solve_line(back_row, back_col, pre_direction, current_direction);   //선 그리기

			//back에 따라 이동
			switch (current_direction)
			{
			case UP:
				back_row--;          //위로 이동
				break;

			case DOWN:
				back_row++;          //아래로 이동
				break;

			case RIGHT:
				back_col++;          //오른쪽으로 이동
				break;

			case LEFT:
				back_col--;          //왼쪽으로 이동
				break;

			default:
				break;

			}

			pre_direction = current_direction;

			//시작 위치로 되돌아 오면 종료
			if (back_row == start_row && back_col == start_col)
			{
				m_staticCanvas.paint_room(back_row, back_col, m_staticCanvas.Maze->maze[back_row][back_col].wall, PURPLE);   //탐색한 방 색칠하여 표시
				m_staticCanvas.solve_line(back_row, back_col, pre_direction, NONE);   //선 그리기
				break;
			}
		}
	}
	else
	{
		//출발점, 시작점을 선택하지 않았을 경우 에러 처리
		CString error;
		error.Format(_T("ERROR:\n출발지와 도착지를 선택하세요."));
		AfxMessageBox(error);        //에러 메시지 박스 출력
	}
	
}

//Exit 버튼
void CProjectDlg::OnBnClickedButton_Exit()
{
	delete m_staticCanvas.Maze;   //미로 메모리 해제
	AfxGetMainWnd()->PostMessageW(WM_CLOSE);
}

//라디오 버튼 체크
void CProjectDlg::OnRadioGroup1Clicked(UINT uiID)
{
	switch (uiID)
	{
	case DFS_Radio:
		m_Radio = 0;
		break;

	case BFS_Radio:
		m_Radio = 1;
		break;

	default:
		break;
	}
}