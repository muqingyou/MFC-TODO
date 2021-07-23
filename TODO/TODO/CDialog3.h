﻿#pragma once


// CDialog3 对话框

class CDialog3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog3)

public:
	CDialog3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString title;
	CDateTimeCtrl ddl;
	afx_msg void OnBnClickedOk();
	CComboBox combo;
};
