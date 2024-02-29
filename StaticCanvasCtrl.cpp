// StaticCanvasCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "StaticCanvasCtrl.h"


// StaticCanvasCtrl

IMPLEMENT_DYNAMIC(StaticCanvasCtrl, CStatic)

StaticCanvasCtrl::StaticCanvasCtrl()
{
	//각각의 pen과 brush 색깔 설정
	whiteBrush = new CBrush(RGB(255, 255, 255));
	purpleBrush = new CBrush(RGB(159, 166, 229));
	yellowBrush = new CBrush(RGB(241, 253, 131));
	redBrush = new CBrush(RGB(255, 0, 0));
	blueBrush = new CBrush(RGB(0, 0, 255));

	blackPen = new CPen(PS_SOLID, 3, RGB(0, 0, 0));
	whitePen = new CPen(PS_SOLID, 3, RGB(255, 255, 255));
	purplePen = new CPen(PS_SOLID, 3, RGB(159, 166, 229));
	yellowPen = new CPen(PS_SOLID, 3, RGB(241, 253, 131));
	redPen = new CPen(PS_SOLID, 3, RGB(255, 0, 0));
	redPen_BOLD = new CPen(PS_SOLID, 5, RGB(255, 0, 0));
	bluePen = new CPen(PS_SOLID, 3, RGB(0, 0, 255));


}

StaticCanvasCtrl::~StaticCanvasCtrl()
{
	//각각의 pen과 brush에 할당된 메모리 해제
	delete whiteBrush;
	delete purpleBrush;
	delete yellowBrush;
	delete redBrush;
	delete blueBrush;

	delete blackPen;
	delete whitePen;
	delete purplePen;
	delete yellowPen;
	delete redPen;
	delete redPen_BOLD;
	delete bluePen;
}


BEGIN_MESSAGE_MAP(StaticCanvasCtrl, CStatic)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// StaticCanvasCtrl 메시지 처리기


void StaticCanvasCtrl::SetLength(int row, int col)
{
	//cell의 크기 설정
	if (rectWindow.Width() / col > rectWindow.Height() / row)
	{
		cell = rectWindow.Height() * 0.8 / row;
	}
	else {
		cell = rectWindow.Width() * 0.8 / col;
	}

	//미로의 길이 설정
	len_x = cell * col;
	len_y = cell * row;

	//미로의 시작 위치 설정
	point_x = (rectWindow.Width() - len_x) / 2;
	point_y = (rectWindow.Height() - len_y) / 2;


	//초기 격자무늬 그리기
	Invalidate();

	CPaintDC dc(this);

	CPen* pOldPen;
	pOldPen = dc.SelectObject(blackPen); 

	//하얀 배경 색칠
	CBrush* oldBrush = dc.SelectObject(whiteBrush);
	dc.FillRect(&rectWindow, whiteBrush);
	dc.SelectObject(oldBrush);   
	
	int x = point_x;   //초기 위치
	int y = point_y;
	dc.MoveTo(x, y);
	
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//하나의 방 그리기
			dc.LineTo(x + cell, y);
			dc.LineTo(x + cell, y + cell);
			dc.LineTo(x, y + cell);
			dc.LineTo(x, y);

			//다음 방 좌표로 이동
			x += cell;
		}

		//다음 행으로 이동
		y += cell;
		x -= cell * col;
		dc.MoveTo(x, y);
	}
	

	dc.SelectObject(pOldPen);
	

	UpdateWindow();
}

void StaticCanvasCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.

	//크기
	GetClientRect(&rectWindow);

	//하얀색 배경
	CBrush* oldBrush = dc.SelectObject(whiteBrush);
	dc.FillRect(&rectWindow, whiteBrush);
	dc.SelectObject(oldBrush);

}

//미로의 방 하나를 그리는 함수
void StaticCanvasCtrl::GenerationMaze(int row, int col, bool wall[] /*벽의 유무*/)
{
	Invalidate();

	CPaintDC dc(this);

	CPen* pOldPen;

	//시작 위치 설정
	int x = point_x + cell * col;
	int y = point_y + cell * row;

	
	//미로 방을 하얀색으로 색칠
	pOldPen = dc.SelectObject(whitePen);

	CBrush* oldBrush = dc.SelectObject(whiteBrush);
	dc.Rectangle(x, y, x + cell, y + cell);

	dc.SelectObject(oldBrush);
	

	//시작 위치로 이동
	dc.MoveTo(x, y);

	
	
	//그리기
	//위쪽 벽
	if (wall[0] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
	}
	x += cell;         //x 축 위치 이동
	dc.LineTo(x, y);   //선 그리기
	
	dc.SelectObject(pOldPen);

	//오른쪽 벽
	if (wall[1] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
	}
	y += cell;         //y 축 위치 이동
	dc.LineTo(x, y);   //선 그리기

	dc.SelectObject(pOldPen);

	//아래쪽 벽
	if (wall[2] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
	}
	x -= cell;         //x 축 위치 이동
	dc.LineTo(x, y);   //선 그리기

	dc.SelectObject(pOldPen);

	//왼쪽 벽
	if (wall[3] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
	}
	y -= cell;         //y 축 위치 이동
	dc.LineTo(x, y);   //선 그리기
	
	dc.SelectObject(pOldPen);
	

	UpdateWindow();
}



//미로의 방 색칠
void StaticCanvasCtrl::paint_room(int row, int col/*미로의 첨자*/, bool wall[] /*벽의 유무*/, int color  /*색깔*/)
{
	Invalidate();

	CPaintDC dc(this);
	CPen* pOldPen = dc.SelectObject(whitePen);

	//시작 위치 설정
	int x = point_x + cell * col;
	int y = point_y + cell * row;


	//색 선택
	CBrush* oldBrush = dc.SelectObject(whiteBrush);

	switch (color)
	{
	case WHITE:
		oldBrush = dc.SelectObject(whiteBrush);  //하얀색 선택
		pOldPen = dc.SelectObject(whitePen);   
		break;

	case PURPLE:
		oldBrush = dc.SelectObject(purpleBrush);  //보라색 선택
		pOldPen = dc.SelectObject(purplePen);  
		break;

	case YELLOW:
		oldBrush = dc.SelectObject(yellowBrush);  //노란색 선택
		pOldPen = dc.SelectObject(yellowPen);  
		break;

	default:
		break;
	}

	//해당 위치의 방 색칠
	dc.Rectangle(x, y, x + cell, y + cell);


	//시작 위치로 이동
	dc.MoveTo(x, y);

	//그리기
	//위쪽 벽
	if (wall[0] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		
		switch (color)
		{
		case WHITE:
			pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
			break;

		case PURPLE:
			pOldPen = dc.SelectObject(purplePen);   //벽이 없으면 보라색
			break;

		case YELLOW:
			pOldPen = dc.SelectObject(yellowPen);   //마우스 호버링 -> 노란색
			break;

		default:
			break;
		}
	}
	x += cell;         //x 축 위치 이동
	dc.LineTo(x, y);   //선 그리기

	dc.SelectObject(pOldPen);

	//오른쪽 벽
	if (wall[1] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		switch (color)
		{
		case WHITE:
			pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
			break;

		case PURPLE:
			pOldPen = dc.SelectObject(purplePen);   //벽이 없으면 보라색
			break;

		case YELLOW:
			pOldPen = dc.SelectObject(yellowPen);   //마우스 호버링 -> 노란색
			break;

		default:
			break;
		}
	}
	y += cell;         //y 축 위치 이동
	dc.LineTo(x, y);   //선 그리기

	dc.SelectObject(pOldPen);

	//아래쪽 벽
	if (wall[2] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		switch (color)
		{
		case WHITE:
			pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
			break;

		case PURPLE:
			pOldPen = dc.SelectObject(purplePen);   //벽이 없으면 보라색
			break;

		case YELLOW:
			pOldPen = dc.SelectObject(yellowPen);   //마우스 호버링 -> 노란색
			break;

		default:
			break;
		}
	}
	x -= cell;         //x 축 위치 이동
	dc.LineTo(x, y);   //선 그리기

	dc.SelectObject(pOldPen);

	//왼쪽 벽
	if (wall[3] == true)
	{
		pOldPen = dc.SelectObject(blackPen);   //벽이 있으면 검은색
	}
	else
	{
		switch (color)
		{
		case WHITE:
			pOldPen = dc.SelectObject(whitePen);   //벽이 없으면 하얀색
			break;

		case PURPLE:
			pOldPen = dc.SelectObject(purplePen);   //벽이 없으면 보라색
			break;

		case YELLOW:
			pOldPen = dc.SelectObject(yellowPen);   //마우스 호버링 -> 노란색
			break;

		default:
			break;
		}
	}
	y -= cell;         //y 축 위치 이동
	dc.LineTo(x, y);   //선 그리기
	

	//출발점인 경우 원 다시 그리기
	if (row == L_Click_current_row && col == L_Click_current_col)
	{
		draw_circle(row, col, RED);
	}

	//도착점인 경우 원 다시 그리기
	if (row == R_Click_current_row && col == R_Click_current_col)
	{
		draw_circle(row, col, BLUE);
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(oldBrush);

	UpdateWindow();
}


void StaticCanvasCtrl::draw_circle(int row, int col ,int color /* 1:빨간색(출발점), 2:파란색(도착점)*/)
{
	Invalidate();

	CPaintDC dc(this);
	CPen* pOldPen = dc.SelectObject(redPen);

	//시작 위치 설정
	int x = point_x + cell * col;
	int y = point_y + cell * row;


	//색 선택
	CBrush* oldBrush = dc.SelectObject(redBrush);


	switch (color)
	{
	case RED:
		//빨간색(출발점)
		pOldPen = dc.SelectObject(redPen);
		oldBrush = dc.SelectObject(redBrush);
		break;

	case BLUE:
		//파란색(도착점)
		pOldPen = dc.SelectObject(bluePen);
		oldBrush = dc.SelectObject(blueBrush);
		break;

	default:
		break;
	}

	dc.Ellipse(x + 2, y + 2, x + cell - 2, y + cell - 2);

	dc.SelectObject(pOldPen);
	dc.SelectObject(oldBrush);

	UpdateWindow();
}


void StaticCanvasCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int x = point.x;    //마우스 커서 x 좌표
	int y = point.y;    //마우스 커서 y 좌표

	//미로 영역에 마우스 커서가 존재할 경우
	if (x > point_x && x < point_x + len_x && y > point_y && y < point_y + len_y)
	{
		current_row = (y - point_y) / cell;   //미로에서 마우스 커서의 행 위치
		current_col = (x - point_x) / cell;   //미로에서 마우스 커서의 열 위치

		//마우스 커서의 위치가 미로 방이 변경되었을 경우
		if (current_row != pre_row || current_col != pre_col)
		{
			if (pre_row != -1 && pre_col != -1)
			{
				//이전의 방을 다시 원래의 색으로 변경
				if (Maze->maze[pre_row][pre_col].visit == true)
				{
					//solving을 했던 방이면 보라색으로 변경
					paint_room(pre_row, pre_col, Maze->maze[pre_row][pre_col].wall, PURPLE);
				}
				else
				{
					paint_room(pre_row, pre_col, Maze->maze[pre_row][pre_col].wall, WHITE);
				}


				//원이 그려져 있는 방은 다시 그리기
				if (pre_row == L_Click_current_row && pre_col == L_Click_current_col)
				{
					draw_circle(pre_row, pre_col, RED);   //클릭한 방에 빨간색 원 그리기
				}
				if (pre_row == R_Click_current_row && pre_col == R_Click_current_col)
				{
					draw_circle(pre_row, pre_col, BLUE);   //클릭한 방에 파란색 원 그리기
				}

			}
			paint_room(current_row, current_col, Maze->maze[current_row][current_col].wall, YELLOW);   //새롭게 이동한 방을 노란색으로 변경

			//원이 그려져 있는 방은 다시 그리기
			if (current_row == L_Click_current_row && current_col == L_Click_current_col)
			{
				draw_circle(current_row, current_col, RED);   //클릭한 방에 빨간색 원 그리기
			}
			if (current_row == R_Click_current_row && current_col == R_Click_current_col)
			{
				draw_circle(current_row, current_col, BLUE);   //클릭한 방에 파란색 원 그리기
			}


			//이전 위치를 현재 위치로 변경
			pre_row = current_row;
			pre_col = current_col;
		}
	}


	CStatic::OnMouseMove(nFlags, point);
}

//마우스 왼쪽 클릭 (출발점 설정)
void StaticCanvasCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int x = point.x;    //마우스 왼쪽 클릭 x 좌표
	int y = point.y;    //마우스 왼쪽 클릭 y 좌표


	//미로 영역에 마우스 커서가 존재할 경우
	if (x > point_x && x < point_x + len_x && y > point_y && y < point_y + len_y)
	{
		L_Click_current_row = (y - point_y) / cell;   //미로에서 마우스 왼쪽 클릭 행 위치
		L_Click_current_col = (x - point_x) / cell;   //미로에서 마우스 왼쪽 클릭 열 위치

		//마우스 왼쪽 클릭 위치가 미로 방이 변경되었을 경우
		if (L_Click_current_row != L_Click_pre_row || L_Click_current_col != L_Click_pre_col)
		{
			if (L_Click_pre_row != -1 && L_Click_pre_col != -1)
			{
				//이전의 방에서 원 삭제
				if (Maze->maze[L_Click_pre_row][L_Click_pre_col].visit == true)
				{
					//solving을 했던 방이면 보라색으로 변경
					paint_room(L_Click_pre_row, L_Click_pre_col, Maze->maze[L_Click_pre_row][L_Click_pre_col].wall, PURPLE);
				}
				else
				{
					paint_room(L_Click_pre_row, L_Click_pre_col, Maze->maze[L_Click_pre_row][L_Click_pre_col].wall, WHITE);
				}
			}
			
			if (L_Click_current_row == L_Click_pre_row && L_Click_current_col == L_Click_pre_col)
			{
				//이미 출발점으로 선택한 위치이면 원 삭제
				if (Maze->maze[L_Click_pre_row][L_Click_pre_col].visit == true)
				{
					//solving을 했던 방이면 보라색으로 변경
					paint_room(L_Click_pre_row, L_Click_pre_col, Maze->maze[L_Click_pre_row][L_Click_pre_col].wall, PURPLE);
				}
				else
				{
					paint_room(L_Click_pre_row, L_Click_pre_col, Maze->maze[L_Click_pre_row][L_Click_pre_col].wall, WHITE);
				}
				L_Click_current_row = -2;
				L_Click_current_col = -2;
			}
			else {
				draw_circle(L_Click_current_row, L_Click_current_col, RED);   //클릭한 방에 빨간색 원 그리기

				//이전 위치를 현재 위치로 변경
				L_Click_pre_row = L_Click_current_row;
				L_Click_pre_col = L_Click_current_col;
			}
		}
	}

	CStatic::OnLButtonDown(nFlags, point);
}

//마우스 오른쪽 클릭 (도착점 설정)
void StaticCanvasCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int x = point.x;    //마우스 오른쪽 클릭 x 좌표
	int y = point.y;    //마우스 오른쪽 클릭 y 좌표


	//미로 영역에 마우스 커서가 존재할 경우
	if (x > point_x && x < point_x + len_x && y > point_y && y < point_y + len_y)
	{
		R_Click_current_row = (y - point_y) / cell;   //미로에서 마우스 오른쪽 클릭 행 위치
		R_Click_current_col = (x - point_x) / cell;   //미로에서 마우스 오른쪽 클릭 열 위치

		//마우스 오른쪽 클릭 위치가 미로 방이 변경되었을 경우
		if (R_Click_current_row != R_Click_pre_row || R_Click_current_col != R_Click_pre_col)
		{
			if (R_Click_pre_row != -1 && R_Click_pre_col != -1)
			{
				//이전의 방에서 원 삭제
				if (Maze->maze[R_Click_pre_row][R_Click_pre_col].visit == true)
				{
					//solving을 했던 방이면 보라색으로 변경
					paint_room(R_Click_pre_row, R_Click_pre_col, Maze->maze[R_Click_pre_row][R_Click_pre_col].wall, PURPLE);
				}
				else
				{
					paint_room(R_Click_pre_row, R_Click_pre_col, Maze->maze[R_Click_pre_row][R_Click_pre_col].wall, WHITE);
				}
			}

			if (R_Click_current_row == R_Click_pre_row && R_Click_current_col == R_Click_pre_col)
			{
				//이미 출발점으로 선택한 위치이면 원 삭제
				if (Maze->maze[R_Click_pre_row][R_Click_pre_col].visit == true)
				{
					//solving을 했던 방이면 보라색으로 변경
					paint_room(R_Click_pre_row, R_Click_pre_col, Maze->maze[R_Click_pre_row][R_Click_pre_col].wall, PURPLE);
				}
				else
				{
					paint_room(R_Click_pre_row, R_Click_pre_col, Maze->maze[R_Click_pre_row][R_Click_pre_col].wall, WHITE);
				}
				R_Click_current_row = -2;
				R_Click_current_col = -2;
			}
			else {
				draw_circle(R_Click_current_row, R_Click_current_col, BLUE);   //클릭한 방에 파란색 원 그리기

				//이전 위치를 현재 위치로 변경
				R_Click_pre_row = R_Click_current_row;
				R_Click_pre_col = R_Click_current_col;
			}
		}
	}


	CStatic::OnRButtonDown(nFlags, point);
}


//Solving -> 경로를 라인으로 그리는 함수
void StaticCanvasCtrl::solve_line(int row, int col, int direction_start, int direction_end)
{
	Invalidate();

	CPaintDC dc(this);
	CPen* pOldPen = dc.SelectObject(redPen_BOLD);

	//경로를 선으로 그리기
	//시작 위치 설정 (direction_start에 따라)
	int x = point_x + (cell * col) + (cell / 2);
	int y = point_y + (cell * row) + (cell / 2);

	if (direction_end == NONE)
	{
		//시작점이므로 빨간색 원 그리기
		draw_circle(row, col, RED);
	}

	//시작 위치부터 중앙 위치까지 선 그리기
	if (direction_start == LEFT)
	{
		//해당 위치로 이동 (이전 back이 왼쪽이므로 오른쪽에서 시작)
		dc.MoveTo(x + (cell / 2), y);

		//중앙 위치까지 선 그리기
		dc.LineTo(x, y);
	}
	else if (direction_start == RIGHT)
	{
		//해당 위치로 이동 (이전 back이 오른쪽이므로 왼쪽에서 시작)
		dc.MoveTo(x - (cell / 2), y);

		//중앙 위치까지 선 그리기
		dc.LineTo(x, y);
	}
	else if (direction_start == UP)
	{
		//해당 위치로 이동 (이전 back이 위쪽이므로 아래쪽에서 시작)
		dc.MoveTo(x, y + (cell / 2));

		//중앙 위치까지 선 그리기
		dc.LineTo(x, y);
	}
	else if (direction_start == DOWN)
	{
		//해당 위치로 이동 (이전 back이 아래쪽이므로 위쪽에서 시작)
		dc.MoveTo(x, y - (cell / 2));

		//중앙 위치까지 선 그리기
		dc.LineTo(x, y);
	}
	else
	{
		//도착점이므로 파란색 원 그리기
		draw_circle(row, col, BLUE);

		//출발 점일 경우 방의 중앙으로 이동 
		dc.MoveTo(x, y);
	}



	//중앙 위치부터 종료 위치까지 선 그리기
	if (direction_end == LEFT)
	{
		//종료 위치로 그리기 (현재 back이 왼쪽이므로 왼쪽으로 그리기)
		dc.LineTo(x - (cell / 2), y);
	}

	if (direction_end == RIGHT)
	{
		//종료 위치로 그리기 (현재 back이 오른쪽이므로 오른쪽으로 그리기)
		dc.LineTo(x + (cell / 2), y);
	}

	if (direction_end == UP)
	{
		//종료 위치로 그리기 (현재 back이 위쪽이므로 위쪽으로 그리기)
		dc.LineTo(x, y - (cell / 2));
	}

	if (direction_end == DOWN)
	{
		//종료 위치로 그리기 (현재 back이 아래쪽이므로 아래쪽으로 그리기)
		dc.LineTo(x, y + (cell / 2));
	}

	dc.SelectObject(pOldPen);

	UpdateWindow();
}



