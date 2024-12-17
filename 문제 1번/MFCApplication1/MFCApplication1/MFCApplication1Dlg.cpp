
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <atlimage.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	InitImage();
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCApplication1Dlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CMFCApplication1Dlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMFCApplication1Dlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CMFCApplication1Dlg::ThreadDisplayCircle(LPVOID param)
{
	CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)param;
	
	int x = (pDlg->m_Point2.x - pDlg->m_Point1.x) / 10;
	int y = (pDlg->m_Point2.y - pDlg->m_Point1.y) / 10;

	for (int i = pDlg->m_Point1.x, j = pDlg->m_Point1.y; i <= pDlg->m_Point2.x; i += x, j += y)
	{
		pDlg->DisplayCircle(i, j);
		pDlg->SaveImage(i, j);
		Sleep(500);
	}

	return 0; //스레드 자동 소멸
}

void CMFCApplication1Dlg::InitImage()
{
	if (!m_Image.IsNull())
	{
		m_Image.Destroy();
	}

	m_nWidth = 640;
	m_nHeight = 480;
	m_Image.Create(m_nWidth, -m_nHeight, 8);

	RGBQUAD rgb[256];
	for (int i = 0; i < 255; i++)
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	m_Image.SetColorTable(0, 256, rgb);
}

void CMFCApplication1Dlg::SaveImage(int x, int y)
{
	// TODO: 여기에 구현 코드 추가.
	TCHAR path[256] = { 0, };
	GetModuleFileName(NULL, path, 256);

	CString str(path);
	CString file;

	str = str.Left(str.ReverseFind('\\')) + _T("\\Image");
	file.Format(_T("\\Image_%d_%d.bmp"), x, y);

	if (GetFileAttributes(str) == -1)
		CreateDirectory(str, NULL);

	str += file;
	m_Image.Save(str);
}

void CMFCApplication1Dlg::DisplayCircle(int x, int y)
{	
	InitImage();

	unsigned char* image = (unsigned char*)m_Image.GetBits();
	int pitch = m_Image.GetPitch();

	memset(image, 0, sizeof(unsigned char) * pitch * m_nHeight);

	for (int j = y - m_nRadius; j < y + m_nRadius; j++)
	{
		if (j < 0 || j >= m_nHeight)
			continue;

		for (int i = x - m_nRadius; i < x + m_nRadius; i++)
		{
			if (i < 0 || i >= m_nWidth)
				continue;

			double dist = (i - x) * (i - x) + (j - y) * (j - y);

			if (dist < (m_nRadius * m_nRadius))
				image[pitch * j + i] = 255;
		}
	}

	CClientDC dc(this);
	m_Image.Draw(dc, 0, 50);

	//m_Image.ReleaseDC();
}

void CMFCApplication1Dlg::OnBnClickedButtonDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Point1.x = GetDlgItemInt(IDC_EDIT_POINT1_X);
	m_Point1.y = GetDlgItemInt(IDC_EDIT_POINT1_Y);

	m_nRadius = rand() % 100;

	DisplayCircle(m_Point1.x, m_Point1.y);
}


void CMFCApplication1Dlg::OnBnClickedButtonAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Point1.x = GetDlgItemInt(IDC_EDIT_POINT1_X);
	m_Point1.y = GetDlgItemInt(IDC_EDIT_POINT1_Y);


	m_Point2.x = GetDlgItemInt(IDC_EDIT_POINT2_X);
	m_Point2.y = GetDlgItemInt(IDC_EDIT_POINT2_Y);

	m_nRadius = 50;

	AfxBeginThread(ThreadDisplayCircle, this);

}

void CMFCApplication1Dlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CString path;
		path.Format(_T("%s\\%s"), dlg.GetFolderPath(), dlg.GetFileName());

		if(!m_Image.IsNull())
			m_Image.Destroy();

		if (m_Image.Load(path) == S_OK)
		{
			unsigned char* image = (unsigned char*)m_Image.GetBits();
			int height = m_Image.GetHeight();
			int pitch = m_Image.GetPitch();

			int minx = 9999;
			int miny = 9999;
			int maxx = 0; 
			int maxy = 0;

			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < -pitch; i++)
				{
					if (image[pitch * j + i] == 255)
					{
						if (minx > i)
							minx = i;

						if (miny > j)
							miny = j;

						if (maxx < i)
							maxx = i;

						if (maxy < j)
							maxy = j;
					}
				}
			}

			int centerx = (minx + maxx) / 2;
			int centery = (miny + maxy) / 2;
			int index = 0;

			for (int j = centery - 10; j < centery + 10; j++)
				image[pitch * j + (centerx - 10 + index++)] = 0;

			index = 0;

			for (int j = centery - 10; j < centery + 10; j++)
				image[pitch * j + (centerx + 10 - index++)] = 0;

			CString center_pos;
			center_pos.Format(_T("%d, %d"), centerx, centery);
			RECT rect;

			rect.left = minx;
			rect.top = maxy;
			rect.right = maxx;
			rect.top = rect.top + 20;

			HDC image_dc = m_Image.GetDC();
			::DrawText(image_dc, center_pos, -1, &rect, DT_CENTER | DT_VCENTER);

			CClientDC dc(this);
			m_Image.Draw(dc, 0, 50);

			m_Image.ReleaseDC();
		}
	}
}
