
// QRDemo2008Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "PictureEx/PictureEx.h"
#include <iostream>

// CQRDemo2008Dlg �Ի���
class CQRDemo2008Dlg : public CDialog
{
// ����
public:
	CQRDemo2008Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QRDEMO2008_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
