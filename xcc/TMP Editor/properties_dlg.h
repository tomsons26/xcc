#if !defined(AFX_PROPERTIES_DLG_H__E85BD5C0_F2FC_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_PROPERTIES_DLG_H__E85BD5C0_F2FC_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// properties_dlg.h : header file
//

#include "cc_structures.h"
#include "resource.h"
#include "virtual_image.h"
#include "XCC TMP EditorDoc.h"

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg dialog
class Cproperties_dlg : public CDialog
{
public:
	void get(t_tmp_image_header& header);
	void set(const t_tmp_image_header& header, CXCCTMPEditorDoc *doc, int id);
	Cproperties_dlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(Cproperties_dlg)
	enum { IDD = IDD_PROPERTIES };
	int		m_height;
	int		m_terrain_type;
	int		m_x;
	int		m_x_extra;
	int		m_y;
	int		m_y_extra;
	int		m_ramp_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cproperties_dlg)
	protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cproperties_dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_red1;
	int m_green1;
	int m_blue1;
	int m_red2;
	int m_green2;
	int m_blue2;
	unsigned int m_hasextra;
	int m_leftmost;

private:
	CXCCTMPEditorDoc *theDoc; // lives the duration the dialog is open for
	int m_currentid;
	
public:
	afx_msg void OnBnClickedAutocolour();

	BOOL m_hasdamaged;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIES_DLG_H__E85BD5C0_F2FC_11D4_B606_0000B4936994__INCLUDED_)