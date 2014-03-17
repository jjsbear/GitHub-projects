
// CatalystMonitorServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CatalystMonitorServer.h"
#include "CatalystMonitorServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
}

CCatalystMonitorServerDlg::~CCatalystMonitorServerDlg()
{
	closesocket(m_socketServer);
	WSACleanup();
}

void CCatalystMonitorServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCatalystMonitorServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Service, &CCatalystMonitorServerDlg::OnBnClickedButtonService)
	ON_BN_CLICKED(IDC_BUTTON_Close, &CCatalystMonitorServerDlg::OnBnClickedButtonClose)
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

	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pPort)
		pPort->SetWindowTextA("1986");

	CreateServerSocket();
	UpdateLocalHostIP();
	LoadDisplayListFromFile();

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

bool CCatalystMonitorServerDlg::AddOneSetting(SocketFeatureData socketData)
{

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
/*	for (DisplayList::iterator itDisplay = m_displayList.begin(); itDisplay != m_displayList.end(); ++itDisplay)
	{
		fprintf(file, "\n");
        fprintf(file, "Display: %s\n", itDisplay->szDisplay);
		for (AdapterList::iterator itAdapter = itDisplay->adapterList.begin(); itAdapter != itDisplay->adapterList.end(); ++itAdapter)
		{
			fprintf(file, "Adapter: %s\n", itAdapter->szAdapter);
			for (SettingList::iterator itSetting = itAdapter->settingList.begin(); itSetting != itAdapter->settingList.end(); ++itSetting)
			{
				char szFormat[256] = "";
				sprintf(szFormat, "%s\n", s_szSettingFormat);
				fprintf(file, szFormat, itSetting->nXResolution, itSetting->nYResolution, itSetting->nColourDepth, itSetting->fRefreshRate, 
                    itSetting->nBrightness, itSetting->nContrast, itSetting->nSaturation, itSetting->nHue, itSetting->nTemperature, itSetting->rate);
                
                fprintf(file, "    GammaR: ");
                for (int i=0; i<256; i++)
                    fprintf(file, "%d,", itSetting->wGamma[0][i]);
                fprintf(file, "\n");

                fprintf(file, "    GammaG: ");
                for (int i=0; i<256; i++)
                    fprintf(file, "%d,", itSetting->wGamma[1][i]);
                fprintf(file, "\n");

                fprintf(file, "    GammaB: ");
                for (int i=0; i<256; i++)
                    fprintf(file, "%d,", itSetting->wGamma[2][i]);
                fprintf(file, "\n");
                fprintf(file, "\n");
			}
		}
	}*/

	fclose(file);
	return true;
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

	char szTemp[256] = "";
	while (fgets(szTemp, sizeof(szTemp), file) != NULL)
	{
		if (strstr(szTemp, "Display: ") == szTemp)
		{

		}
		else if (strstr(szTemp, "Adapter: ") == szTemp)
		{

		}
		
		memset(szTemp, 0, sizeof(szTemp));
	}

	fclose(file);
	return true;
}

/*
void CCatalystMonitorServerDlg::ClearOneDisplay(strDisplay& display)
{
	memset(display.szDisplay, 0, sizeof(display.szDisplay));
	for (AdapterList::iterator itAdapter = display.adapterList.begin(); itAdapter != display.adapterList.end(); ++itAdapter)
		ClearOneAdapter(*itAdapter);

	display.adapterList.clear();
}

void CCatalystMonitorServerDlg::ClearOneAdapter(strAdapter& adapter)
{
	memset(adapter.szAdapter, 0, sizeof(adapter.szAdapter));
	adapter.settingList.clear();
}*/

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

