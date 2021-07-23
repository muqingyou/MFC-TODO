// CDialog3.cpp: 实现文件
//

#include "pch.h"
#include "CDialog3.h"
#include "TODO.h"		// 主符号
#include "afxdialogex.h"


// CDialog3 对话框

IMPLEMENT_DYNAMIC(CDialog3, CDialogEx)

CDialog3::CDialog3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, title(_T(""))
{

}

CDialog3::~CDialog3()
{
}

void CDialog3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, title);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, ddl);
	DDX_Control(pDX, IDC_COMBO1, combo);
}


BEGIN_MESSAGE_MAP(CDialog3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog3::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialog3 消息处理程序
BOOL CDialog3::OnInitDialog() {
	CDialogEx::OnInitDialog();
	TCHAR szDateTime[20] = { 0 };
	CString num;
	for (int i = 1; i < 10; i++) {
		sprintf_s(szDateTime, _T("%d"), i);
		num = szDateTime;
		combo.AddString(num);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



void CDialog3::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SYSTEMTIME ddlTime = { 0 };
	ddl.GetTime(&ddlTime);//获取当前控件的时间
	TCHAR szDateTime[20] = { 0 };
	sprintf_s(szDateTime, _T("%02d-%02d-%02d"), ddlTime.wYear, ddlTime.wMonth, ddlTime.wDay);
	ddlTime.wHour = 0;
	ddlTime.wMinute = 0;
	ddlTime.wSecond = 0;
	ddlTime.wMilliseconds = 0;

	CString str = szDateTime;
	//写文件
	CStdioFile file;
	BOOL isOK = file.Open("../todo.txt", CFile::modeWrite);
	if (isOK == FALSE) {
		return;
	}

	UpdateData(TRUE);
	file.SeekToEnd();
	file.WriteString(title);
	file.WriteString("\n");
	file.WriteString(str);
	file.WriteString("\n");

	//计算
	SYSTEMTIME nowTime = { 0 };
	GetLocalTime(&nowTime);
	nowTime.wHour = 0;
	nowTime.wMinute = 0;
	nowTime.wSecond = 0;
	nowTime.wMilliseconds = 0;
	/*WORD wYear;WORD wMonth;WORD wDayOfWeek;WORD wDay;WORD wHour;WORD wMinute;WORD wSecond;WORD wMilliseconds;SYSTEMTIME该结构体包含详细的年月日时分秒并不适于计算*/
	FILETIME ft_begin, ft_end;
	//从1601年1月1日到今天的纳秒数，是另一种类型结构体
	SystemTimeToFileTime(&nowTime, &ft_begin);
	SystemTimeToFileTime(&ddlTime, &ft_end);
	//相当于对filetime进行的初始化
	/*typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;包括高位和低位，并不能直接相减，这里引入一个联合体ULARGE_INTEGER*/
	ULARGE_INTEGER u_begin, u_end;
	u_begin.u.HighPart = ft_begin.dwHighDateTime;
	u_begin.u.LowPart = ft_begin.dwLowDateTime;
	u_end.u.HighPart = ft_end.dwHighDateTime;
	u_end.u.LowPart = ft_end.dwLowDateTime;
	ULONGLONG ull_span;//用来存差值（纳秒）
	//无符号数减法
	ull_span = u_begin.QuadPart >= u_end.QuadPart ? (u_begin.QuadPart - u_end.QuadPart) : (u_end.QuadPart - u_begin.QuadPart); 

	ULONGLONG ull_seconds = ull_span / 10000000;
	int n_minutes = ull_seconds / 60;
	int n_hours = n_minutes / 60;
	int n_day = n_hours / 24;//计算相应的日时分秒
	n_day = u_begin.QuadPart > u_end.QuadPart ? (0 - n_day) : (n_day);

	CString span;
	sprintf_s(szDateTime, _T("%d"), n_day);
	span = szDateTime;
	file.WriteString(span);
	file.WriteString("\n");

	//预期用时
	int nIndex = combo.GetCurSel();
	CString strCBText;
	combo.GetLBText(nIndex, strCBText);
	file.WriteString(strCBText);
	file.WriteString("\n");

	file.Close();

	CDialog::OnOK();
}
