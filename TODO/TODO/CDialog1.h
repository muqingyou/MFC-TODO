# ifndef _CDIALOG1_H_
# define _CDIALOG1_H_

	#include "Thing.h"
	bool  cmp(const Thing& a, const Thing& b);
	// CDialog1 对话框

	class CDialog1 : public CDialogEx
	{
		DECLARE_DYNAMIC(CDialog1)

	public:
		CDialog1(CWnd* pParent = nullptr);   // 标准构造函数
		virtual ~CDialog1();

		// 对话框数据
	#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_DIALOG1 };
	#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		BOOL OnInitDialog();
		DECLARE_MESSAGE_MAP()
	public:
		CListCtrl todo;
		afx_msg void OnClickedButtonRead();
		afx_msg void OnClickedButtonAdd();
	};

# endif 
