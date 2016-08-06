// properties_dlg.cpp : implementation file
//
#include "stdafx.h"
#include "properties_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg dialog

Cproperties_dlg::Cproperties_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cproperties_dlg::IDD, pParent)
	, m_red1(0)
	, m_green1(0)
	, m_blue1(0)
	, m_red2(0)
	, m_green2(0)
	, m_blue2(0)
	, m_hasdamaged(FALSE)
{
	//{{AFX_DATA_INIT(Cproperties_dlg)
	m_height = 0;
	m_terrain_type = 0;
	m_x = 0;
	m_x_extra = 0;
	m_y = 0;
	m_y_extra = 0;
	m_ramp_type = 0;
	//}}AFX_DATA_INIT
}

void Cproperties_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cproperties_dlg)
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDV_MinMaxInt(pDX, m_height, 0, 127);
	DDX_Text(pDX, IDC_TERRAIN_TYPE, m_terrain_type);
	DDV_MinMaxInt(pDX, m_terrain_type, 0, 127);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_X_EXTRA, m_x_extra);
	DDX_Text(pDX, IDC_Y, m_y);
	DDX_Text(pDX, IDC_Y_EXTRA, m_y_extra);
	DDX_Text(pDX, IDC_RAMP_TYPE, m_ramp_type);
	DDV_MinMaxInt(pDX, m_ramp_type, 0, 127);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_RED1, m_red1);
	DDV_MinMaxInt(pDX, m_red1, 0, 255);
	DDX_Text(pDX, IDC_GREEN1, m_green1);
	DDV_MinMaxInt(pDX, m_green1, 0, 255);
	DDX_Text(pDX, IDC_BLUE1, m_blue1);
	DDV_MinMaxInt(pDX, m_blue1, 0, 255);
	DDX_Text(pDX, IDC_RED2, m_red2);
	DDV_MinMaxInt(pDX, m_red2, 0, 255);
	DDX_Text(pDX, IDC_GREEN2, m_green2);
	DDV_MinMaxInt(pDX, m_green2, 0, 255);
	DDX_Text(pDX, IDC_BLUE2, m_blue2);
	DDV_MinMaxInt(pDX, m_blue2, 0, 255);
	DDX_Check(pDX, IDC_CHECK1, m_hasdamaged);
}

BEGIN_MESSAGE_MAP(Cproperties_dlg, CDialog)
	//{{AFX_MSG_MAP(Cproperties_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_AUTOCOLOUR, OnBnClickedAutocolour)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg message handlers

void Cproperties_dlg::set(const t_tmp_image_header& header, CXCCTMPEditorDoc *doc, int id)
{
	m_x = header.x;
	m_y = header.y;
	if (header.has_extra_data)
	{
		m_x_extra = header.x_extra;
		m_y_extra = header.y_extra;
	}
	else
	{
		m_x_extra = 0;
		m_y_extra = 0;
	}
	m_height = header.height;
	m_terrain_type = header.terrain_type;
	m_ramp_type = header.ramp_type;

	// Why, Olaf, why? (added Radar Colours!!)
	m_red1 = header.radar_red_left;
	m_green1 = header.radar_green_left;
	m_blue1 = header.radar_blue_left;
	m_red2 = header.radar_red_right;
	m_green2 = header.radar_green_right;
	m_blue2 = header.radar_blue_right;

	m_hasextra = header.has_extra_data;
	m_hasdamaged = static_cast<bool>(header.has_damaged_data);

	theDoc = doc;
	m_currentid = id;
	m_leftmost = theDoc->get_rect().x;
}

void Cproperties_dlg::get(t_tmp_image_header& header)
{
	header.x = m_x;
	header.y = m_y;
	header.x_extra = m_x_extra;
	header.y_extra = m_y_extra;
	header.height = m_height;
	header.terrain_type = m_terrain_type;
	header.ramp_type = m_ramp_type;
	header.has_damaged_data = static_cast<int>(m_hasdamaged);

	header.radar_red_left = m_red1;
	header.radar_green_left = m_green1;
	header.radar_blue_left = m_blue1;
	header.radar_red_right = m_red2;
	header.radar_green_right = m_green2;
	header.radar_blue_right = m_blue2;

	theDoc = NULL;
}

void Cproperties_dlg::OnBnClickedAutocolour()
{
	unsigned int count = 0;
	int x, y, pixel8; // save various stuff in order to
	int w, h, wx, hx; // avoid having to get() it each time
	unsigned int r = 0, g = 0, b = 0;
	unsigned int factor = 4; // multiplier to cell brightness

	Cvirtual_image imgmain, imgextra;
	t_palet_entry *pal;

	// Number of pixels wide the left-side extra is (Cutting Point)
	// (Right Shift = cutoff at zero. Left Shift = cutoff at wx.)
	// Theory 2: Always shift right unless it's the leftmost tile.

#define EXTRA_DATA_MID ((m_x == m_leftmost) ? (w/2 + m_x - m_x_extra) : 0)

	imgmain = theDoc->get_image(m_currentid);
	pal = (t_palet_entry *)imgmain.palet();
	w = imgmain.cx();
	h = imgmain.cy();

	// cheap imitation of cliff darkening effect (which happens to be correct ^_^)
	factor = ((m_height > 0) && (m_ramp_type == 0)) ? 3 : 4;

	if (m_hasextra)
	{
		imgextra = theDoc->get_extra_image(m_currentid);
		wx = imgextra.cx();
		hx = imgextra.cy();
	}

	// left pixel
	// main
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w/2; x++)
		{
			pixel8 = imgmain.pixel8(x, y);
			if (pixel8 > 0) // not transparent
			{
				r += (pal[pixel8].r/4)*factor; // 18-bit colours: we want to round
				g += (pal[pixel8].g/4)*factor; // down in order to undo XCC's
				b += (pal[pixel8].b/4)*factor; // wrongful 0-255 brightness 'correction'
				count++;
			}
		}
	}
	// extra
	if (m_hasextra)
	{
		for (y = 0; y < hx; y++)
		{
			for (x = 0; x < min(EXTRA_DATA_MID, wx); x++)
			{
				pixel8 = imgextra.pixel8(x, y);
				if (pixel8 > 0) // not transparent
				{
					r += (pal[pixel8].r/4)*factor;
					g += (pal[pixel8].g/4)*factor;
					b += (pal[pixel8].b/4)*factor;
					count++;
				}
			}
		}
	}

	if (count == 0) count = 1;

	r /= count; g /= count; b /= count;
	r = (r > 255) ? 255 : r;
	g = (g > 255) ? 255 : g; // unneeded but just making sure... =D
	b = (b > 255) ? 255 : b;

	SetDlgItemInt(IDC_RED1, r, false);
	SetDlgItemInt(IDC_GREEN1, g, false);
	SetDlgItemInt(IDC_BLUE1, b, false);

	// right pixel
	r = g = b = count = 0;
	for (y = 0; y < h; y++)
	{
		for (x = w/2; x < w; x++)
		{
			pixel8 = imgmain.pixel8(x, y);
			if (pixel8 > 0) // not transparent
			{
				r += (pal[pixel8].r/4)*factor;
				g += (pal[pixel8].g/4)*factor;
				b += (pal[pixel8].b/4)*factor;
				count++;
			}
		}
	}
	// extra
	if (m_hasextra)
	{
		for (y = 0; y < hx; y++)
		{
			for (x = max(EXTRA_DATA_MID, 0); x < wx; x++)
			{
				pixel8 = imgextra.pixel8(x, y);
				if (pixel8 > 0) // not transparent
				{
					r += (pal[pixel8].r/4)*factor;
					g += (pal[pixel8].g/4)*factor;
					b += (pal[pixel8].b/4)*factor;
					count++;
				}
			}
		}
	}
	if (count == 0) count = 1;

	r /= count; g /= count; b /= count;
	r = (r > 255) ? 255 : r;
	g = (g > 255) ? 255 : g; // unneeded but just making sure... =D
	b = (b > 255) ? 255 : b;

	SetDlgItemInt(IDC_RED2, r, false);
	SetDlgItemInt(IDC_GREEN2, g, false);
	SetDlgItemInt(IDC_BLUE2, b, false);
}