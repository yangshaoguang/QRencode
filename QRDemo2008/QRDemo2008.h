
// QRDemo2008.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQRDemo2008App:
// �йش����ʵ�֣������ QRDemo2008.cpp
//

class CQRDemo2008App : public CWinAppEx
{
public:
	CQRDemo2008App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQRDemo2008App theApp;