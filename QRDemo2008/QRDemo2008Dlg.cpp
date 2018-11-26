
// QRDemo2008Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QRDemo2008.h"
#include "QRDemo2008Dlg.h"

#include <string.h>
#include <errno.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>


// #include "qrencode.h"
#include "LibQREncode/qrencode.h"

#define QRCODE_TEXT					"http://www.baidu.com";		// Text to encode into QRCode
#define OUT_FILE					"C:/test.bmp"								// Output file name
#define OUT_FILE_PIXEL_PRESCALER	8											// Prescaler (number of pixels in bmp file for each QRCode pixel, on each dimension)

#define PIXEL_COLOR_R				0											// Color of bmp pixels
#define PIXEL_COLOR_G				0
#define PIXEL_COLOR_B				0

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CQRDemo2008Dlg 对话框




CQRDemo2008Dlg::CQRDemo2008Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQRDemo2008Dlg::IDD, pParent)
	, m_strDes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQRDemo2008Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_BUTTON1, m_gen);
	DDX_Text(pDX, IDC_EDIT1, m_strDes);
	DDX_Control(pDX, IDC_STATIC_PIC, m_pic);
}

BEGIN_MESSAGE_MAP(CQRDemo2008Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CQRDemo2008Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CQRDemo2008Dlg 消息处理程序

BOOL CQRDemo2008Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQRDemo2008Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQRDemo2008Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQRDemo2008Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string CQRDemo2008Dlg::CStringToString(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}
void CQRDemo2008Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_edit.m_hWnd)
		m_edit.MoveWindow(0, cy-20, cx - 90, 20);
	if (m_gen.m_hWnd)
		m_gen.MoveWindow(cx - 80, cy - 20, 90, 20);
}

void CQRDemo2008Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	const char*			szSourceSring;// = QRCODE_TEXT;
	std::string url = /*cs_utf8*/CStringToString(m_strDes);
	szSourceSring = url.c_str();

	unsigned int	unWidth, x, y, l, n, unWidthAdjusted, unDataBytes;
	unsigned char*	pRGBData, *pSourceData, *pDestData;
	QRcode*			pQRC;
	FILE*			f;

	/*
	* Create a symbol from the string. The library automatically parses the input
	* string and encodes in a QR Code symbol.
	* @warning This function is THREAD UNSAFE when pthread is disabled.
	* @param string input string. It must be NUL terminated.
	* @param version version of the symbol. If 0, the library chooses the minimum
	*                version for the given input data.
	* @param level error correction level.
	* @param hint tell the library how non-alphanumerical characters should be
	*             encoded. If QR_MODE_KANJI is given, kanji characters will be
	*             encoded as Shif-JIS characters. If QR_MODE_8 is given, all of
	*             non-alphanumerical characters will be encoded as is. If you want
	*             to embed UTF-8 string, choose this.
	* @param casesensitive case-sensitive(1) or not(0).
	* @return an instance of QRcode class. The version of the result QRcode may
	*         be larger than the designated version. On error, NULL is returned,
	*         and errno is set to indicate the error. See Exceptions for the
	*         details.
	* @throw EINVAL invalid input object.
	* @throw ENOMEM unable to allocate memory for input objects.
	* @throw ERANGE input data is too large.
	*/

	// Compute QRCode

	if (pQRC = QRcode_encodeString(url.c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1))
	{
		unWidth = pQRC->width;
		unWidthAdjusted = unWidth * OUT_FILE_PIXEL_PRESCALER * 3;
		if (unWidthAdjusted % 4)
			unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
		unDataBytes = unWidthAdjusted * unWidth * OUT_FILE_PIXEL_PRESCALER;

		// Allocate pixels buffer

		if (!(pRGBData = (unsigned char*)malloc(unDataBytes)))
		{
			AfxMessageBox(L"Out of memory");
			return;
		}

		// Preset to white

		memset(pRGBData, 0xff, unDataBytes);


		// Prepare bmp headers

		BITMAPFILEHEADER kFileHeader;
		kFileHeader.bfType = 0x4d42;  // "BM"
		kFileHeader.bfSize = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER) +
			unDataBytes;
		kFileHeader.bfReserved1 = 0;
		kFileHeader.bfReserved2 = 0;
		kFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER);

		BITMAPINFOHEADER kInfoHeader;
		kInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		kInfoHeader.biWidth = unWidth * OUT_FILE_PIXEL_PRESCALER;
		kInfoHeader.biHeight = -((int)unWidth * OUT_FILE_PIXEL_PRESCALER);
		kInfoHeader.biPlanes = 1;
		kInfoHeader.biBitCount = 24;
		kInfoHeader.biCompression = BI_RGB;
		kInfoHeader.biSizeImage = 0;
		kInfoHeader.biXPelsPerMeter = 0;
		kInfoHeader.biYPelsPerMeter = 0;
		kInfoHeader.biClrUsed = 0;
		kInfoHeader.biClrImportant = 0;


		// Convert QrCode bits to bmp pixels

		pSourceData = pQRC->data;
		for (y = 0; y < unWidth; y++)
		{
			pDestData = pRGBData + unWidthAdjusted * y * OUT_FILE_PIXEL_PRESCALER;
			for (x = 0; x < unWidth; x++)
			{
				if (*pSourceData & 1)
				{
					for (l = 0; l < OUT_FILE_PIXEL_PRESCALER; l++)
					{
						for (n = 0; n < OUT_FILE_PIXEL_PRESCALER; n++)
						{
							*(pDestData + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_B;
							*(pDestData + 1 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_G;
							*(pDestData + 2 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_R;
						}
					}
				}
				pDestData += 3 * OUT_FILE_PIXEL_PRESCALER;
				pSourceData++;
			}
		}


		// Output the bmp file

		if (!(fopen_s(&f, OUT_FILE, "wb")))
		{
			fwrite(&kFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
			fwrite(&kInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
			fwrite(pRGBData, sizeof(unsigned char), unDataBytes, f);

			fclose(f);
		}
		else
		{
			printf("Unable to open file");
			exit(-1);
		}

		// Free data

		free(pRGBData);
		QRcode_free(pQRC);
	}
	else
	{
		//printf("NULL returned");
		//exit(-1);
	}
	CString s = L"C:/test.bmp";
	if (m_pic.Load(s))
		m_pic.Draw();
}
