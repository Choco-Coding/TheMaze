#pragma once

// StaticCanvasCtrl
#include "MAZE.h"


class StaticCanvasCtrl : public CStatic
{
	DECLARE_DYNAMIC(StaticCanvasCtrl)

public:
	StaticCanvasCtrl();
	virtual ~StaticCanvasCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CRect rectWindow;            //canvas 크기

	CBrush* whiteBrush;          //하얀색 brush
	CBrush* purpleBrush;           //보라색 brush
	CBrush* yellowBrush;           //노란색 brush
	CBrush* redBrush;           //빨간색 brush
	CBrush* blueBrush;           //파란색 brush

	CPen* blackPen;              //검은색 pen
	CPen* whitePen;              //하얀색 pen
	CPen* purplePen;              //보라색 pen
	CPen* yellowPen;            //노란색 pen
	CPen* redPen;            //빨간색 pen
	CPen* redPen_BOLD;            //두꺼운 빨간색 pen
	CPen* bluePen;            //파란색 pen

	int len_x;                   //미로의 가로 길이
	int len_y;                   //미로의 세로 길이

	int row;                  //미로의 행
	int col;                  //미로의 열
	
	int cell;                  //방 하나의 길이

	int point_x;               //미로의 시작 x 좌표
	int point_y;               //미로의 시작 y 좌표

	int current_row = -2;         //미로에서 마우스 커서의 현재 행 위치
	int current_col = -2;         //미로에서 마우스 커서의 현재 열 위치

	int pre_row = -1;      //미로에서 마우스 커서의 이전 행 위치
	int pre_col = -1;      //미로에서 마우스 커서의 이전 열 위치

	//마우스 좌 클릭
	int L_Click_current_row = -2;         //미로에서 마우스 왼쪽 클릭의 현재 행 위치
	int L_Click_current_col = -2;         //미로에서 마우스 왼쪽 클릭의 현재 열 위치

	int L_Click_pre_row = -1;        //미로에서 마우스 왼쪽 클릭의 이전 행 위치
	int L_Click_pre_col = -1;        //미로에서 마우스 왼쪽 클릭의 이전 열 위치

	//마우스 우 클릭
	int R_Click_current_row = -2;         //미로에서 마우스 오른쪽 클릭의 현재 행 위치
	int R_Click_current_col = -2;         //미로에서 마우스 오른쪽 클릭의 현재 열 위치

	int R_Click_pre_row = -1;        //미로에서 마우스 오른쪽 클릭의 이전 행 위치
	int R_Click_pre_col = -1;        //미로에서 마우스 오른쪽 클릭의 이전 열 위치

	afx_msg void OnPaint();    //하얀색 배경

	void SetLength(int row, int col);  //미로의 크기 설정

	void GenerationMaze(int row, int col/*미로의 첨자*/, bool wall[] /*벽의 유무*/);         //미로 그리기
	void paint_room(int row, int col/*미로의 첨자*/, bool wall[] /*벽의 유무*/, int color  /*색깔*/);      //미로의 방 색칠
	void draw_circle(int row, int col, int color /* 1:빨간색(출발점), 2:파란색(도착점)*/);

	void solve_line(int row, int col, int direction_start, int direction_end);                    //Solving -> 길을 라인으로 그리는 함수



	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	MAZE* Maze = nullptr;                                         //미로


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

