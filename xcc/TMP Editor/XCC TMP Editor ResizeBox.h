#pragma once

#include "cc_structures.h"
#include "Resource.h"

// CXCCTMPEditorResizeBox dialog

class CXCCTMPEditorResizeBox : public CDialog
{
	DECLARE_DYNAMIC(CXCCTMPEditorResizeBox)

public:
	CXCCTMPEditorResizeBox(CWnd* pParent = NULL);   // standard constructor
	virtual ~CXCCTMPEditorResizeBox();

// Dialog Data
	enum { IDD = IDD_RESIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_width;
	int m_height;

	void set(t_tmp_ts_header header);
	void get(t_tmp_ts_header *header);
};
