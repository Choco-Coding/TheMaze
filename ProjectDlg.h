
// ProjectDlg.h: 헤더 파일
//

#pragma once

#include "StaticCanvasCtrl.h"

// CProjectDlg 대화 상자
class CProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Row;                                       //text editor ; 행
	CEdit m_Column;                                    //text editor ; 열
	
	int row;                                           //행
	int col;                                           //열

	afx_msg void OnBnClickedButton_Generate();          //Generate 버튼
	afx_msg void OnBnClickedButton_Solve();             //Solve 버튼
	afx_msg void OnBnClickedButton_Exit();              //Exit 버튼

	StaticCanvasCtrl m_staticCanvas;

	CButton m_Animation_G;                              //Generate의 Animation 체크박스
	CButton m_Animation_S;                              //Solving의 Animation 체크박스

	int m_Radio = 0;                                        //라디오 버튼의 체크 상태 (0:DFS, 1:BFS)

	afx_msg void OnRadioGroup1Clicked(UINT uiID);        //라디오 버튼
};

