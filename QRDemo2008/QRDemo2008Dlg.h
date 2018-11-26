
// QRDemo2008Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "PictureEx/PictureEx.h"
#include <iostream>

// CQRDemo2008Dlg 对话框
class CQRDemo2008Dlg : public CDialog
{
// 构造
public:
	CQRDemo2008Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QRDEMO2008_DIALOG };

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
	CEdit m_edit;
	CButton m_gen;
	CString m_strDes;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	std::string CStringToString(LPCWSTR pwszSrc);
	afx_msg void OnBnClickedButton1();
	CPictureEx m_pic;
};
