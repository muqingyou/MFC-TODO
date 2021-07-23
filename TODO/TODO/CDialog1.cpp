// CDialog1.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "TODO.h"
#include "CDialog1.h"
#include "afxdialogex.h"
#include "CDialog3.h"

#include <vector>
#include<algorithm>
using namespace std;

// CDialog1 对话框

IMPLEMENT_DYNAMIC(CDialog1, CDialogEx)

CDialog1::CDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, todo);
}


BEGIN_MESSAGE_MAP(CDialog1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog1::OnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog1::OnClickedButtonAdd)
END_MESSAGE_MAP()


// CDialog1 消息处理程序
BOOL CDialog1::OnInitDialog() {
	CDialogEx::OnInitDialog();
	todo.InsertColumn(0, _T("待办"), LVCFMT_LEFT, 80);
	todo.InsertColumn(1, _T("截止日期"), LVCFMT_LEFT, 100);
	todo.InsertColumn(2, _T("剩余天数"), LVCFMT_LEFT, 80);
	todo.InsertColumn(3, _T("预计课时"), LVCFMT_LEFT, 80);
	todo.SetExtendedStyle(todo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDialog1::OnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	//read
	CFile file;
	BOOL isOK = file.Open("../todo.txt", CFile::modeRead);
	if (isOK == FALSE) {
		return;
	}
	CArchive ar(&file, CArchive::load);

	vector<Thing> todoVector;
	Thing todoItem = Thing("","",0,0);
	int i = 0;
	CString strTemp;
	while (ar.ReadString(strTemp)) {
		if (i % 4 == 0)
			todoItem.title = strTemp;
		else if (i % 4 == 1) {
			todoItem.ddl = strTemp;
		}
		else if (i % 4 == 2) {
			todoItem.span = _ttoi(strTemp);
		}
		else {
			todoItem.need = _ttoi(strTemp);
			todoVector.push_back(todoItem);
		}
		i++;
	}

	//排序
	sort(todoVector.begin(), todoVector.end(), cmp);

	todo.DeleteAllItems();
	for (int i = 0; i < todoVector.size(); i++) {
		todo.InsertItem(i, todoVector[i].title);
		todo.SetItemText(i, 1, todoVector[i].ddl);
		CString cStr;
		cStr.Format(_T("%d"), todoVector[i].span);
		todo.SetItemText(i, 2, cStr);
		cStr.Format(_T("%d"), todoVector[i].need);
		todo.SetItemText(i, 3, cStr);
	}
	ar.Close();
	file.Close();
}

void CDialog1::OnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog3 dlg3;
	dlg3.DoModal();
}

bool  cmp(const Thing& a, const Thing& b) {
	return a.span < b.span;
}
