
// AhmetBilal's Bit CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AhmetBilal's Bit Calculator.h"
#include "AhmetBilal's Bit CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAhmetBilalsBitCalculatorDlg dialog



CAhmetBilalsBitCalculatorDlg::CAhmetBilalsBitCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAhmetBilalsBitCalculatorDlg::IDD, pParent)
	, check_and(0)
	, checck_or(0)
	, check_xor(0)
	, option(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAhmetBilalsBitCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, input1);
	DDX_Control(pDX, IDC_EDIT2, input2);
	DDX_Control(pDX, IDC_COMBO1, advanced_text);
	DDX_Control(pDX, IDC_CHECK1, shift);
	DDX_Control(pDX, IDC_EDIT3, bit_num);
	DDX_Radio(pDX, IDC_RADIO1, option);
	DDX_Control(pDX, IDC_LIST1, list);
}

BEGIN_MESSAGE_MAP(CAhmetBilalsBitCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAhmetBilalsBitCalculatorDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAhmetBilalsBitCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CAhmetBilalsBitCalculatorDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &CAhmetBilalsBitCalculatorDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CAhmetBilalsBitCalculatorDlg message handlers

BOOL CAhmetBilalsBitCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	advanced_text.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAhmetBilalsBitCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAhmetBilalsBitCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAhmetBilalsBitCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAhmetBilalsBitCalculatorDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

int maxSize = 0;

void CAhmetBilalsBitCalculatorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CString o1, o2, direction, b_num, myResult;
	int result;
	bool shift_check = true; // it is true if shift is given and false if it is not given

	CDC *pDC = GetDC(); // taken from document to arrange scroll bar
	CSize cz;		   // taken from document to arrange scroll bar

	input1.GetWindowTextW(o1);
	input2.GetWindowTextW(o2);

	unsigned int op1 = _tcstoul(o1, nullptr, 10);
	unsigned int op2 = _tcstoul(o2, nullptr, 10);

	// checking whether the operand are missing or not
	if(input1.GetWindowTextLengthW() == 0){
		myResult = _T("At least one operand was not entered.");
	}
	else if (input2.GetWindowTextLengthW() == 0){
		myResult = _T("At least one operand was not entered.");
	}
	else{
		// enabling combobox if the user selects shift
		if(shift.GetCheck() == 1){
			int selected_id = advanced_text.GetCurSel();
			advanced_text.GetLBText(selected_id, direction);

			bit_num.GetWindowTextW(b_num);
			// checking the num bit input
			if(bit_num.GetWindowTextLengthW() == 0){
				myResult = _T("Specify how many bits you want to shift");

				// updating shift check
				shift_check = false;
			}
			else if(shift_check){
				int num = _ttoi(b_num);
	
				if(direction == "Left"){
					op1 = op1 << num;
					op2 = op2 << num;
					// updating new nums
					o1.Format(_T("%u"), op1);
					o2.Format(_T("%u"), op2);
				}
				else{
					op1 = op1 >> num;
					op2 = op2 >> num;
					// updating new nums
					o1.Format(_T("%u"), op1);
					o2.Format(_T("%u"), op2);
				}
			}
		}

		if(shift_check){
			
			// getting the option of radio button (the operand)
			UpdateData(TRUE);

			if(option == 0){
				result = op1 & op2;
				myResult.Format(_T("%u"), result);
				myResult = o1 + _T(" AND ") + o2 + _T(" = ") + myResult;
	
			}
			else if(option == 1){
				result = op1 | op2;
				myResult.Format(_T("%u"), result);
				myResult = o1 + _T(" OR ") + o2 + _T(" = ") + myResult;
			}
			else{ // if option == 2
				result = op1 ^ op2;
				myResult.Format(_T("%u"), result);
				myResult = o1 + _T(" XOR ") + o2 + _T(" = ") + myResult;
	
			}

		}


	}
	// printing myResult
	list.AddString(myResult);
	// arranging the scroll bar taken from GUI document
	cz = pDC->GetTextExtent(myResult);
	if(cz.cx > maxSize){
		maxSize = cz.cx;
	}
	list.SetHorizontalExtent(maxSize);
}


void CAhmetBilalsBitCalculatorDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	// enabling the bit_num and advanced_text(combobox)
	if(shift.GetCheck()){
	
		advanced_text.EnableWindow(TRUE);
		bit_num.EnableWindow(TRUE);
	}
	else { // if shift did not clicked

		advanced_text.EnableWindow(FALSE);
		bit_num.EnableWindow(FALSE);

	}

}


void CAhmetBilalsBitCalculatorDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}
