
// CatalystMonitorServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CatalystMonitorServer.h"
#include "CatalystMonitorServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VISUAL_WIDTH 600
#define VISUAL_HEIGHT 200

static char s_szDisplayList[] = "CatalystMonitorServer.data";
static char s_szVPPFlag[] = "Catalyst Monitor Server";
static char s_szSettingFormat[] = "XRes: %d, YRes: %d, Color: %d, RefreshRate: %f, Brightness: %d, Contrast: %d, Saturation: %d, Hue: %d, Temperature: %d, Rate: %d";
static char s_szServiceLog[] = "CatalystMonitorService.log";

void ThreadReceiveSendData(LPVOID param);
void ThreadSOCKETSpeedTest(LPVOID param);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCatalystMonitorServerDlg dialog
CCatalystMonitorServerDlg::CCatalystMonitorServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatalystMonitorServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_socketServer = NULL;
	m_hThread = NULL;
	m_bTerminateThread = false;

	m_updateDisplay = false;
	m_nStride = (VISUAL_WIDTH*3+3)/4*4;
	m_dataFeatures = new byte[m_nStride*VISUAL_HEIGHT];
    memset(m_dataFeatures, 0xFF, m_nStride*VISUAL_HEIGHT);

	HDC hDC = ::GetDC(::GetDesktopWindow());
	HDC memDC = CreateCompatibleDC(hDC);
	BITMAPINFOHEADER bmpNewInfo = {sizeof(BITMAPINFOHEADER), VISUAL_WIDTH, VISUAL_HEIGHT, 1, 24, BI_RGB, m_nStride*VISUAL_HEIGHT, 0, 0, 0, 0};

    void *	pData = 0;
	m_bitmapFeatures = CreateDIBSection(memDC, (BITMAPINFO*)&bmpNewInfo, DIB_RGB_COLORS, &pData, NULL, 0);
	SetDIBits(memDC, m_bitmapFeatures, 0, VISUAL_HEIGHT, m_dataFeatures, (BITMAPINFO*)&bmpNewInfo, DIB_RGB_COLORS);
	DeleteDC (memDC);
	::ReleaseDC (::GetDesktopWindow(), hDC);
}

CCatalystMonitorServerDlg::~CCatalystMonitorServerDlg()
{
	closesocket(m_socketServer);
	WSACleanup();
    m_listClientsFeatures.clear();

	if (m_bitmapFeatures)
		DeleteObject(m_bitmapFeatures);
	delete[] m_dataFeatures;
}

void CCatalystMonitorServerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_Client, m_ComboBoxClient);
}

BEGIN_MESSAGE_MAP(CCatalystMonitorServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Service, &CCatalystMonitorServerDlg::OnBnClickedButtonService)
	ON_BN_CLICKED(IDC_BUTTON_Close, &CCatalystMonitorServerDlg::OnBnClickedButtonClose)
    ON_CBN_SELCHANGE(IDC_COMBO_Client, &CCatalystMonitorServerDlg::OnCbnSelchangeComboClient)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCatalystMonitorServerDlg message handlers

BOOL CCatalystMonitorServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	CWnd* pFeaturesChage = GetDlgItem(IDC_STATIC_FeaturesChange);
	if (pFeaturesChage)
	{
		pFeaturesChage->GetWindowRect(&m_rectFeaturesChange);
		ScreenToClient(&m_rectFeaturesChange);
        pFeaturesChage->MoveWindow(m_rectFeaturesChange.left, m_rectFeaturesChange.top, VISUAL_WIDTH, VISUAL_HEIGHT);

		pFeaturesChage->GetWindowRect(&m_rectFeaturesChange);
		ScreenToClient(&m_rectFeaturesChange);
    }
    
    CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pPort)
		pPort->SetWindowTextA("1986");

	CreateServerSocket();
	UpdateLocalHostIP();
	LoadDisplayListFromFile();

	SetTimer(1, 500, NULL);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCatalystMonitorServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCatalystMonitorServerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCatalystMonitorServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCatalystMonitorServerDlg::CreateServerSocket()
{
	WSADATA wsa = {};
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{        
		AfxMessageBox("Socket initialization failed!", MB_ICONERROR);
		return;    
	}

	if((m_socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		AfxMessageBox("Socket creation failed!", MB_ICONERROR);
		m_socketServer = NULL;
		return;
	}

	if (m_socketServer) // nonblocking mode
	{
		ULONG arg = 1;
		ioctlsocket(m_socketServer, FIONBIO, &arg);
	}
}

void CCatalystMonitorServerDlg::UpdateLocalHostIP()
{   
	CWnd* pHost = GetDlgItem(IDC_EDIT_Host);
	if (pHost == NULL)
		return;
	
	char host_name[255] = "";
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR)
	{
		pHost->SetWindowTextA("NA");
		return;
	}
	else
	{
		pHost->SetWindowTextA(host_name);
	}

	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	if (pIP == NULL)
		return;

	struct hostent *phe = gethostbyname(host_name);
	if (phe == 0)
	{
		pIP->SetWindowTextA("NA");
	}
	else
	{
		struct in_addr addr = {};
		memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
		char* szIP = inet_ntoa(addr);
		pIP->SetWindowTextA(szIP);
	}
}

void CCatalystMonitorServerDlg::OnBnClickedButtonService()
{
	if (InitializeService() == false)
		return;

	CWnd* pService = GetDlgItem(IDC_BUTTON_Service);
	if (pService)
        pService->EnableWindow(FALSE);

	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pPort)
		pPort->EnableWindow(FALSE);

#ifdef SOCKETSPEEDTEST
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadSOCKETSpeedTest, (LPVOID)this, 0, NULL);
#else
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadReceiveSendData, (LPVOID)this, 0, NULL);
#endif
}

bool CCatalystMonitorServerDlg::InitializeService()
{
	if (m_socketServer == NULL)
		return false;

	short nPort = 1986;
	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pPort)
	{
		CString strPort;
		pPort->GetWindowTextA(strPort);
		nPort = atoi(strPort.GetBuffer());
	}

	sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(nPort);
	if(bind(m_socketServer, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		AfxMessageBox("Socket binding failed, please try with other port!", MB_ICONERROR);
		return false;
	}

	if(listen(m_socketServer, SOMAXCONN )== SOCKET_ERROR)
	{
		AfxMessageBox("Socket listening failed!", MB_ICONERROR);
		return false;
	}
	return true;
}

void ThreadReceiveSendData(LPVOID param)
{
	CCatalystMonitorServerDlg* displayServer = static_cast<CCatalystMonitorServerDlg*>(param);

	while(displayServer)
	{
		if (displayServer->m_bTerminateThread)
			return;

		SOCKET clientSocket = NULL;
		if (displayServer->CreateClientSocket(clientSocket) == false) // nonblocking socket here, otherwise waiting until a connection is created
		{
			Sleep(500);
			continue;
		}
		Sleep(200); // Wait for Client's sending, specially for nonblocking socket

		int bytes = 0;
		char buf[BUFFERLENGTH] = "";
		if((bytes = recv(clientSocket, buf, sizeof(buf) ,0)) != SOCKET_ERROR)
		{
			buf[bytes] = '\0';
			if (bytes < sizeof(SocketFeatureData)) // connection test
			{
				SocketTestData data = {};
				memcpy(&data, buf, min(sizeof(data), bytes));
				if (data.type == DataType::test)
					send(clientSocket, (char*)&data, sizeof(data), 0);
			}
			else
			{
				SocketFeatureData data = {};
				memcpy(&data, buf, min(sizeof(data), bytes));
				if (data.type == DataType::ClientSetting) // client current setting
				{
					if (displayServer->AddOneSetting(data))
    					displayServer->RecordService(data);

					data.type = DataType::ServerReceived;
					send(clientSocket, (char*)&data, sizeof(data), 0);
				}
			}
		}
		closesocket(clientSocket);
	}
}

bool CCatalystMonitorServerDlg::CreateClientSocket(SOCKET& clientSocket)
{
	sockaddr_in clientAddress;
	memset(&clientAddress,0,sizeof(clientAddress));
	int addrlen = sizeof(clientAddress);
	if((clientSocket = accept(m_socketServer, (sockaddr*)&clientAddress, &addrlen)) == INVALID_SOCKET) // return immediately for nonblocking mode
	{        
		//AfxMessageBox("Socket accepts client failed!", MB_ICONERROR); // No message for nonblocking socket mode
		return false;
	} 
	return true;
}

bool CCatalystMonitorServerDlg::AddOneSetting(SocketFeatureData socketData)
{
	int i;
	for (i=0; i< m_listClientsFeatures.size(); i++)
    {
        if (stricmp(socketData.szHostName, m_listClientsFeatures[i].szHostName) == 0)
        {
            for (int j=0; j<FEATURECOUNT; j++)
            {
                if (socketData.featureChanges[j].nChanged > 0)
                    m_listClientsFeatures[i].featureChanges[j].nChanged++;
            }
			break;
        }
    }
    
    if (i == m_listClientsFeatures.size()) // new client
    {
        ClientFeatures client;
        strcpy(client.szHostName, socketData.szHostName);
        memcpy(client.featureChanges, socketData.featureChanges, sizeof(strFeatureChange)*FEATURECOUNT);
        m_listClientsFeatures.push_back(client);

		m_ComboBoxClient.AddString(client.szHostName);
		if (m_ComboBoxClient.GetCount() == 1) // only one client
			m_ComboBoxClient.SetCurSel(0);
    }

	if (m_ComboBoxClient.GetCurSel() == i)
		m_updateDisplay = true;

	return true;
}

void ThreadSOCKETSpeedTest(LPVOID param)
{
	CCatalystMonitorServerDlg* displayServer = static_cast<CCatalystMonitorServerDlg*>(param);

	while(displayServer)
	{
		if (displayServer->m_bTerminateThread)
			return;

		SOCKET clientSocket = NULL;
		if (displayServer->CreateClientSocket(clientSocket) == false) // nonblocking socket here, otherwise waiting until a connection is created
		{
			Sleep(500);
			continue;
		}
	//	Sleep(200); // Wait for Client's sending, specially for nonblocking socket

        double time;
        LARGE_INTEGER liOld, liNew, liFreq;
        QueryPerformanceCounter(&liOld);
        
        int nCount = 0;
        int nFail = 0;
        while (!displayServer->m_bTerminateThread)
        {
		    int bytes = 0;
		    char buf[10241] = "";
		    if((bytes = recv(clientSocket, buf, sizeof(buf)-1 ,0)) != SOCKET_ERROR)
		    {
                nCount += bytes;

			    buf[bytes] = '\0';
			    SocketTestData data = {};
			    //memcpy(&data, buf, min(sizeof(data), bytes));

                if (data.type == DataType::test)
			    {
				    send(clientSocket, (char*)&data, sizeof(data), 0);
			    }			    
                else if (data.type == DataType::speedTest)
			    {
				    //send(clientSocket, (char*)&data, sizeof(data), 0);
			    }
		    }
            else
            {
                //WSAGetLastError();
                nFail++;

                if (nCount >= 200000000)
                {
                    QueryPerformanceCounter(&liNew);
                    QueryPerformanceFrequency(&liFreq);
                    time = (liNew.QuadPart - liOld.QuadPart)/(double)(liFreq.QuadPart);

                    char szOutput[256];
                    sprintf(szOutput, "received data length=%d, time=%f, speed=%fMB/s\n", nCount, time, nCount/time/1000000);
                    OutputDebugString(szOutput);
                    break;
                }
            }
        }

		closesocket(clientSocket);
	}
}

bool CCatalystMonitorServerDlg::LoadDisplayListFromFile()
{
	CString strFile = GetModulePath();
	strFile.Append(s_szDisplayList);
	FILE* file = fopen(strFile, "r");
	if (file == NULL)
		return false;

	char szFlag[256] = "";
	fgets(szFlag, 256, file);
	if (strstr(szFlag, s_szVPPFlag) != szFlag)
	{
		fclose(file);
		return false;
	}

	m_listClientsFeatures.clear();

	int index = 0;
	bool bGetClient = false;
	ClientFeatures clientFeature = {};
	
	char szTemp[256] = "";
	while (fgets(szTemp, sizeof(szTemp), file) != NULL)
	{
		if (strstr(szTemp, "Client: ") == szTemp)
		{
			if (bGetClient)
			{
				m_listClientsFeatures.push_back(clientFeature);
				memset(&clientFeature, 0, sizeof(ClientFeatures));
			}

			index = 0;
			bGetClient = true;
			strcpy(clientFeature.szHostName, szTemp+8);
		}
		else if (bGetClient)
		{
			char name[32]="";
			int value=-2;
			sscanf(szTemp, "%s: %d", name, &value);
			if (strlen(name) > 0 && value >=-1)
			{
				strcpy(clientFeature.featureChanges[index].szFeature, name);
				clientFeature.featureChanges[index].nChanged = value;
				index++;
			}
		}
		
		memset(szTemp, 0, sizeof(szTemp));
	}

	fclose(file);
	return true;
}

bool CCatalystMonitorServerDlg::SaveDisplayListToFile()
{
	CString strFile = GetModulePath();
	strFile.Append(s_szDisplayList);
	FILE* file = fopen(strFile, "w");
	if (file == NULL)
		return false;

	fprintf(file, "%s\n", s_szVPPFlag);
	for (ListClientsFeatures::iterator iterator = m_listClientsFeatures.begin(); iterator!=m_listClientsFeatures.end(); ++iterator)
	{
		fprintf(file, "\n");
		fprintf(file, "Client: %s\n", iterator->szHostName);
		for (int i=0; i<FEATURECOUNT; i++)
			fprintf(file, "%s: %d\n", iterator->featureChanges[i].szFeature, iterator->featureChanges[i].nChanged);
	}

	fclose(file);
	return true;
}

bool CCatalystMonitorServerDlg::RecordService(SocketFeatureData& socketData)
{
	CString strFile = GetModulePath();
	strFile.Append(s_szServiceLog);
	FILE* file = fopen(strFile, "a");
	if (file == NULL)
		return false;

	SYSTEMTIME time = {};
	GetLocalTime(&time);
	fprintf(file, "[ %4.4d_%2.2d_%2.2d-%2.2d_%2.2d_%2.2d ] ", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	if (socketData.type == DataType::ClientSetting)
	{
		fprintf(file, "[Client Name:%s] Client sends current setting to server\n", socketData.szHostName);

        fprintf(file, "\n");
    }
	else if (socketData.type == DataType::ServerReceived)
	{
		fprintf(file, "[Client Name:%s] Server receives client's setting\n", socketData.szHostName);
	}

    fprintf(file, "\n");
	fclose(file);
	return true;
}

void CCatalystMonitorServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_updateDisplay)
	{
		CreateFeaturesDisplayData();
		m_updateDisplay = false;
	}
	DisplayFeaturesHistogram();

	CDialog::OnTimer(nIDEvent);
}

void CCatalystMonitorServerDlg::CreateFeaturesDisplayData()
{
	int index = m_ComboBoxClient.GetCurSel();
	if (index==-1 || index >= m_listClientsFeatures.size())
    {
        memset(m_dataFeatures, 0, m_nStride*VISUAL_HEIGHT);
    }
    else
    {
		strFeatureChange* pFeatureData = m_listClientsFeatures[index].featureChanges;

        byte* pDestR = m_dataFeatures;
        for (int i=0; i<VISUAL_HEIGHT; i++)
        {
            for (int j=0; j<VISUAL_WIDTH; j++)
            {
				if (i < pFeatureData[j].nChanged)
                    pDestR[3*j] = pDestR[3*j+1] = pDestR[3*j+2] = 0;
                else
                    pDestR[3*j] = pDestR[3*j+1] = pDestR[3*j+2] = 255;
            }
            pDestR += m_nStride;
        }
    }
}

void CCatalystMonitorServerDlg::DisplayFeaturesHistogram()
{
	CDC memDC;
	CDC *pDC = GetDC();
	memDC.CreateCompatibleDC( pDC);
    
    BITMAP bm;
	GetObject(m_bitmapFeatures, sizeof(BITMAP), &bm);
	memcpy(bm.bmBits, m_dataFeatures, bm.bmWidthBytes*bm.bmHeight);
	HBITMAP pOldBmp = (HBITMAP)memDC.SelectObject(m_bitmapFeatures);
	pDC->BitBlt(m_rectFeaturesChange.left, m_rectFeaturesChange.top, VISUAL_WIDTH, VISUAL_HEIGHT, &memDC, 0, 0,SRCCOPY);
	memDC.SelectObject( pOldBmp);

	memDC.DeleteDC();
	ReleaseDC(pDC);
}

void CCatalystMonitorServerDlg::OnCbnSelchangeComboClient()
{
	CreateFeaturesDisplayData();
}

void CCatalystMonitorServerDlg::OnClose()
{
	OnBnClickedButtonClose();
}

void CCatalystMonitorServerDlg::OnBnClickedButtonClose()
{
	if (m_hThread)
	{
		m_bTerminateThread = true;
		WaitForSingleObject(m_hThread, 2000); //INFINITE
		CloseHandle(m_hThread);
	}
	OnOK();
}

CString CCatalystMonitorServerDlg::GetModulePath()
{
	char szTemp[512] = "";
	char szDrive[8] = "";
	char dir[512] = "";
	char fname[64] = "";
	char ext[64] = "";

	int nLength = GetModuleFileName(NULL, szTemp, sizeof(szTemp));
	_splitpath(szTemp, szDrive, dir, fname, ext);

	CString strTemp;
	strTemp.Format("%s%s", szDrive, dir);
	return strTemp;
}