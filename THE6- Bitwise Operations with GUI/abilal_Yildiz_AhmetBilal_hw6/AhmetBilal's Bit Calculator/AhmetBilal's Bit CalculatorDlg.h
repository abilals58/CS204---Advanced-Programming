
// AhmetBilal's Bit CalculatorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CAhmetBilalsBitCalculatorDlg dialog
class CAhmetBilalsBitCalculatorDlg : public CDialogEx
{
// Construction
public:
	CAhmetBilalsBitCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AHMETBILALSBITCALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CEdit input1;
	CEdit input2;
	int check_and;
	int checck_or;
	int check_xor;
	CComboBox advanced_text;
	CButton shift;
	CEdit bit_num;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	int option;
	CListBox list;
};
