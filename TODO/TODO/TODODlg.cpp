
// TODODlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "framework.h"
#include "TODO.h"
#include "TODODlg.h"
#include "afxdialogex.h"
#include <locale.h> 

#include "CDialog1.h"

#include <vector>
#include<algorithm>

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CAboutDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CTODODlg 对话框



CTODODlg::CTODODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TODO_DIALOG, pParent)
	, name(_T(""))
	, check(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTODODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lesson);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_COMBO2, combo2);
	DDX_Text(pDX, IDC_EDIT2, name);
	DDX_Check(pDX, IDC_CHECK1, check);
}

BEGIN_MESSAGE_MAP(CTODODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTODODlg::OnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON2, &CTODODlg::OnClickedButtonTODO)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTODODlg::OnClickList1)
//	ON_EN_CHANGE(IDC_EDIT1, &CTODODlg::OnEnChangeEdit1)
//	ON_BN_CLICKED(IDC_BUTTON3, &CTODODlg::OnBnClickedButton3)
ON_CBN_SELCHANGE(IDC_COMBO1, &CTODODlg::OnSelchangeCombo1)
ON_CBN_SELCHANGE(IDC_COMBO2, &CTODODlg::OnSelchangeCombo2)
ON_EN_CHANGE(IDC_EDIT2, &CTODODlg::OnChangeName)
ON_BN_CLICKED(IDC_CHECK1, &CTODODlg::OnClickedCheck1)
ON_EN_KILLFOCUS(IDC_EDIT2, &CTODODlg::OnKillfocusEdit2)
END_MESSAGE_MAP()


// CTODODlg 消息处理程序

BOOL CTODODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	lesson.InsertColumn(0, _T("周一"), LVCFMT_LEFT, 80);
	lesson.InsertColumn(1, _T("周二"), LVCFMT_LEFT, 80);
	lesson.InsertColumn(2, _T("周三"), LVCFMT_LEFT, 80);
	lesson.InsertColumn(3, _T("周四"), LVCFMT_LEFT, 80);
	lesson.InsertColumn(4, _T("周五"), LVCFMT_LEFT, 80);
	lesson.InsertColumn(5, _T("周六"), LVCFMT_LEFT, 80);
	lesson.InsertColumn(6, _T("周七"), LVCFMT_LEFT, 80);

	lesson.SetExtendedStyle(lesson.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	 combo1.AddString("一");
	 combo1.AddString("二");
	 combo1.AddString("三");
	 combo1.AddString("四");
	 combo1.AddString("五");
	 combo1.AddString("六");
	 combo1.AddString("日");

	 CString num;
	 for (int i = 1; i <= 12; i++) {
		 num.Format("%d", i);
		 combo2.AddString(num);
	 }

	 for (int i = 0; i < 12; i++) {
		 for (int j = 0; j < 7; j++) {
			 isTodo[i][j] = false;
		 }
	 }

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTODODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTODODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTODODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTODODlg::OnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	//读课表
	CFile file;
	BOOL isOK = file.Open("../lesson.txt", CFile::modeRead);
	if (isOK == FALSE) {
		return;
	}
	CArchive ar(&file, CArchive::load);
	CString str[84];
	CString strTemp;
	int i = 0;

	while (ar.ReadString(strTemp)) {
		str[i]=strTemp;
		i++;
	}


	CString buf;
	CString bufTmp;
	lesson.DeleteAllItems();
	for (int i = 0; i < 84; i++) {
		if(i<12)
			lesson.InsertItem(i, str[i]);
		else
			lesson.SetItemText(i%12, i/12, str[i]);
	}
	ar.Close();
	file.Close();

	//读todo
	CString readStr;
	CStdioFile todoFile;
	isOK = todoFile.Open("../todo.txt", CFile::modeRead);
	if (isOK == FALSE) {
		return;
	}
	vector<Thing> todoVector;
	Thing todoItem = Thing("", "", 0, 0);
	CString str1,str2,str3,str4;
	i = 0;
	BOOL isAdd = true;
	while (todoFile.ReadString(strTemp)) {
		if (i % 4 == 0) {
			todoItem.title = strTemp;
			str1 = strTemp;
		}	
		else if (i % 4 == 1) {
			todoItem.ddl = strTemp;
			str2 = strTemp;
		}
		else if (i % 4 == 2) {
			todoItem.span = _ttoi(strTemp);
			//删除过期
			if (todoItem.span < 0) {
				isAdd = false;
			}
		}
		else {
			todoItem.need = _ttoi(strTemp);
			if (isAdd)
				todoVector.push_back(todoItem);
			else
				isAdd = true;
		}
		i++;
	}

	todoFile.Close();

	//排序
	sort(todoVector.begin(), todoVector.end(), cmp);

	// 删除后的写入
	isOK = todoFile.Open("../todo.txt", CFile::modeCreate | CFile::modeWrite);
	if (isOK == FALSE) {
		return;
	}
	CString span;
	for (int i = 0; i < todoVector.size(); i++) {
		todoFile.WriteString(todoVector[i].title);
		todoFile.WriteString("\n");
		todoFile.WriteString(todoVector[i].ddl);
		todoFile.WriteString("\n");
		span.Format("%d", todoVector[i].span);
		todoFile.WriteString(span);
		todoFile.WriteString("\n");
		span.Format("%d", todoVector[i].need);
		todoFile.WriteString(span);
		todoFile.WriteString("\n");
	}
	todoFile.Close();

	//todo插入课表
	int num = 0;
	int nRow = lesson.GetItemCount();
	int nCol = lesson.GetHeaderCtrl()->GetItemCount();
	//从今天起往后插入
	SYSTEMTIME nowTime = { 0 };
	GetLocalTime(&nowTime);//wDayOfWeek0星期日
	for (int i = (nowTime.wDayOfWeek +6)%7; i < nCol; i++)
	{
		for (int j = 0; j < nRow; j++)
		{
			CString readStr = lesson.GetItemText(j, i);
			if (readStr.GetLength() == 0) {
				if (num < todoVector.size()) {
					if (todoVector[num].need > 0) {
						lesson.SetItemText(j, i, todoVector[num].title);
						isTodo[j][i] = true;
						todoVector[num].need = todoVector[num].need - 1;
						if (todoVector[num].need == 0)
							num++;
					}
				}
			}
		}
	}
	
	//插入修改
	CStdioFile modifyFile;
	isOK = modifyFile.Open("../modify.txt", CFile::modeRead);
	if (isOK == FALSE) {
		return;
	}
	CString rowStr, colStr,content,tempStr;
	int pos;
	while (modifyFile.ReadString(tempStr)) {
		pos = tempStr.Find(',');
		rowStr = tempStr.Left(pos);
		int row = _ttoi(rowStr);
		tempStr = tempStr.Right(tempStr.GetLength() - pos - 1);
		pos = tempStr.Find(',');
		colStr = tempStr.Left(pos);
		int col = _ttoi(colStr);
		content = tempStr.Right(tempStr.GetLength() - pos - 1);
		lesson.SetItemText(col, row, content);
	}
	modifyFile.Close();

}



void CTODODlg::OnClickedButtonTODO()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog1 dlg1;
	dlg1.DoModal();
}


void CAboutDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码

}



void CTODODlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		CString strtemp;
		//strtemp.Format("单击的是第%d行第%d列", pNMListView->iItem, pNMListView->iSubItem);
		
		combo1.SetCurSel(pNMListView->iSubItem);
		combo2.SetCurSel(pNMListView->iItem);
		OnSelchangeCombo1();
	}
	*pResult = 0;
}


void CTODODlg::OnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//CString strRow;
	int rowIndex = combo1.GetCurSel();
	//combo1.GetLBText(rowIndex, strRow);

	//CString strCol;
	int colIndex = combo2.GetCurSel();
	//combo2.GetLBText(colIndex, strCol);
	name = lesson.GetItemText(colIndex, rowIndex);

	check = isTodo[colIndex][rowIndex];

	UpdateData(false);
}


void CTODODlg::OnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	int rowIndex = combo1.GetCurSel();
	int colIndex = combo2.GetCurSel();
	name = lesson.GetItemText(colIndex, rowIndex);

	check = isTodo[colIndex][rowIndex];
	
	UpdateData(false);
}


void CTODODlg::OnChangeName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int rowIndex = combo1.GetCurSel();
	int colIndex = combo2.GetCurSel();
	lesson.SetItemText(colIndex, rowIndex, name);
	
}


void CTODODlg::OnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (check == true) {
		check == false;
	}
	else {
		check == true;
	}
	int rowIndex = combo1.GetCurSel();
	int colIndex = combo2.GetCurSel();
	isTodo[colIndex][rowIndex] = check;
	UpdateData(false);
}


void CTODODlg::OnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改写入modify
	CStdioFile modifyFile;
	bool isOK = modifyFile.Open("../modify.txt", CFile::modeWrite);
	if (isOK == FALSE) {
		return;
	}
	modifyFile.SeekToEnd();
	CString rowStr, colStr;
	int rowIndex = combo1.GetCurSel();
	int colIndex = combo2.GetCurSel();
	rowStr.Format("%d", rowIndex);
	colStr.Format("%d", colIndex);
	modifyFile.WriteString(rowStr+","+colStr+","+name+"\n");
	modifyFile.Close();
}
