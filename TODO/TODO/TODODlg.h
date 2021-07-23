
// TODODlg.h: 头文件
//

# ifndef _TODODLG_H_
# define _TODODLG_H_

	// CTODODlg 对话框
	class CTODODlg : public CDialogEx
	{
	// 构造
	public:
		CTODODlg(CWnd* pParent = nullptr);	// 标准构造函数
		bool isTodo[12][7];

	// 对话框数据
	#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_TODO_DIALOG };
	#endif

		protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
	protected:
		HICON m_hIcon;

		// 生成的消息映射函数
		virtual BOOL OnInitDialog();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		DECLARE_MESSAGE_MAP()
	public:
		CListCtrl lesson;
		afx_msg void OnClickedButtonRead();
		afx_msg void OnClickedButtonTODO();
		afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
//		CString row;
//		CString col;
//		afx_msg void OnEnChangeEdit1();
//		afx_msg void OnBnClickedButton3();
		afx_msg void OnClickedButtonEdit();
		CComboBox combo1;
		CComboBox combo2;
		CString name;
		afx_msg void OnSelchangeCombo1();
		afx_msg void OnSelchangeCombo2();
		afx_msg void OnChangeName();
		BOOL check;
		afx_msg void OnClickedCheck1();
		afx_msg void OnKillfocusEdit2();
	};
# endif