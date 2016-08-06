// XCC TMP Editor ResizeBox.cpp : implementation file
//

#include "stdafx.h"
#include "XCC TMP Editor.h"
#include "XCC TMP Editor ResizeBox.h"


// CXCCTMPEditorResizeBox dialog

IMPLEMENT_DYNAMIC(CXCCTMPEditorResizeBox, CDialog)
CXCCTMPEditorResizeBox::CXCCTMPEditorResizeBox(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCTMPEditorResizeBox::IDD, pParent)
	, m_width(0)
	, m_height(0)
{
}

CXCCTMPEditorResizeBox::~CXCCTMPEditorResizeBox()
{
}

void CXCCTMPEditorResizeBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
}

void CXCCTMPEditorResizeBox::set(t_tmp_ts_header header)
{
	m_width = header.cblocks_x;
	m_height = header.cblocks_y;
}

void CXCCTMPEditorResizeBox::get(t_tmp_ts_header *header)
{
	header->cblocks_x = m_width;
	header->cblocks_y = m_height;
}


BEGIN_MESSAGE_MAP(CXCCTMPEditorResizeBox, CDialog)
END_MESSAGE_MAP()


// CXCCTMPEditorResizeBox message handlers
