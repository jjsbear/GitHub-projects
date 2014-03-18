
// CatalystMonitorClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CatalystMonitorClient.h"
#include "CatalystMonitorClientDlg.h"
#include "..\\include\\ADLMultiMedia.h"
#include "..\\include\\socket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static ADLMultiMedia s_ADLMultiMedia;
static char s_szIniFile[] = "CatalystMonitorClient.ini";
static char s_szVPPClientFlag[] = "Catalyst Monitor Client";

void ThreadDetectCatalystSettingChange(LPVOID param);
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


// CCatalystMonitorClientDlg dialog
CCatalystMonitorClientDlg::CCatalystMonitorClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatalystMonitorClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nIP = 0;
	m_nPort = 0;
	m_hThread = NULL;
	m_bTerminateThread = false;
	m_bConnected = false;
	memset(&m_socketData, 0, sizeof(m_socketData));

    m_lpFeatureCaps = NULL;
	m_lpFeatureValues = NULL;
    m_nFeatureCount = 0;
}

CCatalystMonitorClientDlg::~CCatalystMonitorClientDlg()
{
	WSACleanup();

    if (m_lpFeatureCaps)
		ADLMultiMedia::ADL_Main_Memory_Free((void**)&m_lpFeatureCaps);
	if (m_lpFeatureValues)
		ADLMultiMedia::ADL_Main_Memory_Free((void**)&m_lpFeatureValues);
}

void CCatalystMonitorClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCatalystMonitorClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Connect, &CCatalystMonitorClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_RADIO_Server, &CCatalystMonitorClientDlg::OnBnClickedRadioServer)
	ON_BN_CLICKED(IDC_RADIO_IP, &CCatalystMonitorClientDlg::OnBnClickedRadioIp)
	ON_BN_CLICKED(IDC_BUTTON_Close, &CCatalystMonitorClientDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CCatalystMonitorClientDlg message handlers

BOOL CCatalystMonitorClientDlg::OnInitDialog()
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


	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		AfxMessageBox("Socket initialization failed!", MB_ICONERROR);

	char szServer[256] = "";
	LoadAllSettings(szServer);

	CheckRadioButton(IDC_RADIO_Server, IDC_RADIO_IP, IDC_RADIO_Server);

	CWnd* pServer = GetDlgItem(IDC_EDIT_Server);
	if (pServer)
		pServer->SetWindowTextA(szServer);

	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	if (pIP)
	{	
		in_addr addr;
		addr.s_addr = m_nIP;
		char* szIP = inet_ntoa(addr);
		pIP->SetWindowTextA(szIP);
		pIP->EnableWindow(FALSE);
	}

	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pPort)
	{
		char szTemp[128] = "";
		sprintf(szTemp, "%d", m_nPort);
		pPort->SetWindowTextA(szTemp);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCatalystMonitorClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCatalystMonitorClientDlg::OnPaint()
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
HCURSOR CCatalystMonitorClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCatalystMonitorClientDlg::OnBnClickedButtonConnect()
{
    CWnd* pServer = GetDlgItem(IDC_EDIT_Server);
	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pServer==NULL || pIP==NULL || pPort==NULL)
		return;

	unsigned long ip = 0;	
	int nSelect = GetCheckedRadioButton(IDC_RADIO_Server, IDC_RADIO_IP);
	if (nSelect == IDC_RADIO_Server)
	{
		CString strServer;
		pServer->GetWindowTextA(strServer);
		if (strServer.GetLength())
		{
			ip = GetServerIP(strServer.GetBuffer());
			if (ip == 0)
			{
				AfxMessageBox("Find server failed, Please try with server IP!", MB_ICONERROR);
				return;
			}
			else
			{
				in_addr addr;
				addr.s_addr = ip;
				char* szIP = inet_ntoa(addr);
				pIP->SetWindowTextA(szIP);
			}
		}
		else
		{
			AfxMessageBox("Please input server name!", MB_ICONERROR);
			return;
		}
	}
	else // get IP directly
	{
		CString strIP;
		pIP->GetWindowTextA(strIP);
		if((ip = inet_addr(strIP.GetBuffer())) == INADDR_NONE)
		{
			AfxMessageBox("Invalid IP address!", MB_ICONERROR);
			return; 
		}
		else
		{
			struct hostent *pHost = gethostbyaddr((char*)&ip, 4, PF_INET);
			if (pHost)
				pServer->SetWindowTextA(pHost->h_name);
		}

	}
	short nPort = 1986;
	CString strPort;
	pPort->GetWindowTextA(strPort);
	nPort = atoi(strPort.GetBuffer());
	if (nPort == 0)
	{
		AfxMessageBox("Please input valid server port!", MB_ICONERROR);
		return;
	}

	m_nIP = ip;
	m_nPort = nPort;

#ifdef SOCKETSPEEDTEST
    m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadSOCKETSpeedTest, (LPVOID)this, 0, NULL);
#else
    if (ConnectionTest(true))
    {
	    if (m_hThread == NULL)
		    m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadDetectCatalystSettingChange, (LPVOID)this, 0, NULL);
		SaveAllSettings();
    }
    else
    {
		AfxMessageBox("Connect to server failed!", MB_ICONERROR);
    }
#endif
}

void ThreadDetectCatalystSettingChange(LPVOID param)
{
	const int nInterval = 2000; // milliseconds
	int nIntervalBetweenChanges = 60000 / nInterval; // 60 000: 1 minutes, 600 000: 10 minutes, time to send current setting to server
	int nCount = nIntervalBetweenChanges;

	CCatalystMonitorClientDlg* displayClient = static_cast<CCatalystMonitorClientDlg*>(param); 
	while (displayClient)
	{
		if (displayClient->m_bTerminateThread)
			return;

        if(displayClient->ConnectionTest(false) == false) // if disconnected to server
        {
            displayClient->EnableDlgItem(TRUE);
        }
        else
        {
            displayClient->EnableDlgItem(FALSE);

		    if(displayClient->DetectSettingChange()) // Detect out Catalyst change
			{
				if (nCount > nIntervalBetweenChanges) // Client sends current setting to server if interval between two changes exceed nIntervalBetweenChanges
				{
					displayClient->ParseSettingChange();
					displayClient->SendCatalystSetting();
					nCount = 0;
				}
				else
					nCount ++;
			}
            else
                nCount ++;

		    if (nCount >= 0x0FFFFFFF) // Dead loop in (nCountToSend+1, 0x0FFFFFFF) if there's not change on client
			    nCount = 0;
        }

		Sleep(nInterval);
	}
}

bool CCatalystMonitorClientDlg::ConnectionTest(bool bMainThread)
{
    if (bMainThread == false)
    {
        if (m_bConnected == false)
            return false;
    }
    
	SOCKET socketTemp;
	if((socketTemp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{ 
		AfxMessageBox("Socket creation failed!", MB_ICONERROR);
        m_bConnected = false;
		return false;  
	}

	sockaddr_in serverAddress;
	memset(&serverAddress,0, sizeof(sockaddr_in));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.S_un.S_addr = m_nIP;
	serverAddress.sin_port = htons(m_nPort);
	if(connect(socketTemp, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) // Wait until Server is up or time out
	{
        m_bConnected = false;
		closesocket( socketTemp);
		return false;
	}

	SocketTestData data = {};
	data.type = DataType::test;
	if(send(socketTemp, (char*)&data, sizeof(data), 0) == SOCKET_ERROR)
	{
        m_bConnected = false;
		closesocket( socketTemp);
		return false;
	}

	int bytes = 0;
	char buf[BUFFERLENGTH] = "";
	if((bytes = recv(socketTemp, buf, sizeof(buf), 0)) == SOCKET_ERROR)
	{
        m_bConnected = false;
		closesocket( socketTemp);
		return false;
	}
	else
		closesocket( socketTemp);

	buf[bytes] = '\0';
	memset(&data, 0, sizeof(data));
	memcpy(&data, buf, min(sizeof(data), bytes));
	if (data.type == DataType::test)
        m_bConnected = true;
    else
        m_bConnected = false;

    return m_bConnected;
}

bool CCatalystMonitorClientDlg::DetectSettingChange()
{
    int nFeatureCount = 0;
    LPADLFeatureValues lpFeatureValues = NULL;    
    
	bool ADL_Err = s_ADLMultiMedia.ADLFeatureValuesGet(0, lpFeatureValues, &nFeatureCount);
	if (lpFeatureValues==NULL)
		return false;
    
	assert(m_nFeatureCount == nFeatureCount || m_nFeatureCount==0);
    if (m_lpFeatureValues == NULL) // first detect
    {
        m_lpFeatureValues = lpFeatureValues;
        lpFeatureValues = NULL;
        m_nFeatureCount = nFeatureCount;
        return false;
    }

    //memset(m_lpFeatureValues, 0, sizeof(ADLFeatureValues)*m_nFeatureCount);
	if (memcmp(m_lpFeatureValues, lpFeatureValues, sizeof(ADLFeatureValues)*m_nFeatureCount) == 0) // no change at all
    {
    	ADLMultiMedia::ADL_Main_Memory_Free((void**)&lpFeatureValues);
        return false;
    }
    else
    {
	    ADLMultiMedia::ADL_Main_Memory_Free((void**)&lpFeatureValues);
	    return true;
    }
}

bool CCatalystMonitorClientDlg::ParseSettingChange()
{
    int nFeatureCount = 0;
    LPADLFeatureCaps lpFeatureCaps = NULL;
    LPADLFeatureValues lpFeatureValues = NULL;    
    
    bool ADL_Err = s_ADLMultiMedia.ADLFeatureCaps(0, lpFeatureCaps, &nFeatureCount);
	ADL_Err = s_ADLMultiMedia.ADLFeatureValuesGet(0, lpFeatureValues, &nFeatureCount);
	if (lpFeatureCaps==NULL || lpFeatureValues==NULL)
    {
        ADLMultiMedia::ADL_Main_Memory_Free((void**)&lpFeatureCaps);
        ADLMultiMedia::ADL_Main_Memory_Free((void**)&lpFeatureValues);
		return false;
    }
    
	assert(m_nFeatureCount == nFeatureCount);

    memset(&m_socketData, 0, sizeof(SocketFeatureData));
    gethostname(m_socketData.szHostName, sizeof(m_socketData.szHostName));

    for (int i=0; i<m_nFeatureCount; i++)
	{ 
        strcpy(m_socketData.featureChanges[i].szFeature, lpFeatureValues[i].Name.FeatureName);

        int nFeatureType = lpFeatureCaps[i].iFeatureProperties & lpFeatureCaps[i].iFeatureMask;
		if (nFeatureType & ADL_FEATURE_PROPERTIES_SUPPORTED) // supported ones
        {
		    if (nFeatureType & ADL_FEATURE_PROPERTIES_TOGGLE)
		    {
                if (m_lpFeatureValues[i].bCurrent != lpFeatureValues[i].bCurrent)
                    m_socketData.featureChanges[i].nChanged = 1;
		    }
		    else
		    {
			    nFeatureType = 	nFeatureType & ADL_FEATURE_PROPERTIES_ADJUSTMASK;
			    if (nFeatureType == ADL_FEATURE_PROPERTIES_INT_RANGE)
			    {
				    if (m_lpFeatureValues[i].iCurrent != lpFeatureValues[i].iCurrent)
                        m_socketData.featureChanges[i].nChanged = 1;
			    }
			    else if (nFeatureType == ADL_FEATURE_PROPERTIES_FLOAT_RANGE)
			    {
				    if (m_lpFeatureValues[i].fCurrent != lpFeatureValues[i].fCurrent)
                        m_socketData.featureChanges[i].nChanged = 1;
			    }
			    else if (nFeatureType == ADL_FEATURE_PROPERTIES_ENUM)
			    {
				    if (m_lpFeatureValues[i].EnumStates != lpFeatureValues[i].EnumStates)
                        m_socketData.featureChanges[i].nChanged = 1;
			    }
		    }
        }
        else // not supported on this adapter
            m_socketData.featureChanges[i].nChanged = -1;
	}
    
    ADLMultiMedia::ADL_Main_Memory_Free((void**)&lpFeatureCaps);
	ADLMultiMedia::ADL_Main_Memory_Free((void**)&m_lpFeatureValues);
    m_lpFeatureValues = lpFeatureValues;
    lpFeatureValues = NULL;
	
	return true;
}

bool CCatalystMonitorClientDlg::SendCatalystSetting()
{
	if (m_bConnected == false)
		return false;

	SOCKET socketTemp;
	if((socketTemp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{ 
		AfxMessageBox("Socket creation failed!", MB_ICONERROR);
        m_bConnected = false;
		return false;  
	}

	sockaddr_in serverAddress;
	memset(&serverAddress,0, sizeof(sockaddr_in));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.S_un.S_addr = m_nIP;
	serverAddress.sin_port = htons(m_nPort);

	bool bSent = false;
	if(connect(socketTemp, (sockaddr*)&serverAddress, sizeof(serverAddress)) != SOCKET_ERROR) // Wait until Server is up or time out
	{
		SocketFeatureData data = m_socketData;
		data.type = DataType::ClientSetting;
		if(send(socketTemp, (char*)&data, sizeof(data), 0) != SOCKET_ERROR)	// Once connection is created, client needs to send() ASAP as server socket is nonblocking
		{
			int bytes = 0;
			char buf[BUFFERLENGTH] = "";
			if((bytes = recv(socketTemp, buf, sizeof(buf), 0)) != SOCKET_ERROR)
			{
				buf[bytes]='\0';

				memset(&data, 0, sizeof(data));
				memcpy(&data, buf, min(sizeof(data), bytes));
				if (data.type == DataType::ServerReceived)
					bSent = true;
			}
		}
	}

	closesocket( socketTemp);
	m_bConnected = bSent;
	return m_bConnected;
}

void ThreadSOCKETSpeedTest(LPVOID param)
{
	CCatalystMonitorClientDlg* displayClient = static_cast<CCatalystMonitorClientDlg*>(param); 
	if (displayClient)
	{
		if (displayClient->m_bTerminateThread)
			return;

     //   displayClient->EnableDlgItem(FALSE);
        displayClient->SocketSpeedTest();
     //   displayClient->EnableDlgItem(TRUE);
	}
}

bool CCatalystMonitorClientDlg::SocketSpeedTest()
{
	SOCKET socketTemp;
	if((socketTemp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{ 
		AfxMessageBox("Socket creation failed!", MB_ICONERROR);
		return false;  
	}

	sockaddr_in serverAddress;
	memset(&serverAddress,0, sizeof(sockaddr_in));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.S_un.S_addr = m_nIP;
	serverAddress.sin_port = htons(m_nPort);
	if(connect(socketTemp, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) // Wait until Server is up or time out
	{
		closesocket( socketTemp);
		return false;
	}

    double time;
    LARGE_INTEGER liOld, liNew, liFreq;
    QueryPerformanceCounter(&liOld);

    int nCount = 1000000;
    int nSucceed = 0;
    int nFail = 0;
    for (int i=0; i<nCount; i++)
    {
	    SocketSpeedData data = {};
	    data.type = DataType::speedTest;
	    if(send(socketTemp, (char*)&data, sizeof(data), 0) == SOCKET_ERROR)
	    {
            nFail++;
		//    closesocket( socketTemp);
		//    return false;
	    }
        else
            nSucceed++;

	/*    int bytes = 0;
	    char buf[BUFFERLENGTH] = "";
	    if((bytes = recv(socketTemp, buf, sizeof(buf), 0)) == SOCKET_ERROR)
	    {
		    closesocket( socketTemp);
		    return false;
	    }
	    else
		    closesocket( socketTemp);

	    buf[bytes] = '\0';
	    memset(&data, 0, sizeof(data));
	    memcpy(&data, buf, min(sizeof(data), bytes));
	    if (data.type == DataType::speedTest)*/
    }

    QueryPerformanceCounter(&liNew);
    QueryPerformanceFrequency(&liFreq);
    time = (liNew.QuadPart - liOld.QuadPart)/(double)(liFreq.QuadPart);

    char szOutput[256];
    sprintf(szOutput, "Sent data= %d, time=%f, speed=%fMB/s\n", nSucceed*sizeof(SocketSpeedData), time, nCount*sizeof(SocketSpeedData)/time/1000000);
    OutputDebugString(szOutput);
    return true;
}

void CCatalystMonitorClientDlg::EnableDlgItem(BOOL bEnable)
{
	CWnd* pServer = GetDlgItem(IDC_EDIT_Server);
	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	CWnd* pRadioServer = GetDlgItem(IDC_RADIO_Server);
	CWnd* pRadioIP = GetDlgItem(IDC_RADIO_IP);
	CWnd* pConnect = GetDlgItem(IDC_BUTTON_Connect);
	if (pServer==NULL || pIP==NULL || pPort==NULL || pRadioServer==NULL || pRadioIP==NULL || pConnect==NULL)
		return;

	if (bEnable)
	{
        if (this->IsWindowVisible() == FALSE)
        {
            this->ShowWindow(SW_SHOWNORMAL);
            this->SetForegroundWindow();
        }

        int	nSelect = GetCheckedRadioButton(IDC_RADIO_Server, IDC_RADIO_IP);
		if (nSelect == IDC_RADIO_Server)
		{
			pServer->EnableWindow(TRUE);
			pIP->EnableWindow(FALSE);
		}
		else
		{
			pServer->EnableWindow(FALSE);
			pIP->EnableWindow(TRUE);
		}
	}
	else
	{
    //    this->ShowWindow(SW_HIDE);
		pServer->EnableWindow(FALSE);
		pIP->EnableWindow(FALSE);
	}

	pRadioServer->EnableWindow(bEnable);
	pRadioIP->EnableWindow(bEnable);
	pPort->EnableWindow(bEnable);
	pConnect->EnableWindow(bEnable);
}

bool CCatalystMonitorClientDlg::SaveAllSettings()
{
	CString strFile = GetModulePath();
	strFile.Append(s_szIniFile);
	FILE* file = fopen(strFile, "w");
	if (file == NULL)
		return false;
	
	fprintf(file, "%s\n\n", s_szVPPClientFlag);

	char szServer[256]="", szIP[256]="", szPort[256]="";
	CWnd* pServer = GetDlgItem(IDC_EDIT_Server);
	if (pServer)
		pServer->GetWindowTextA(szServer, sizeof(szServer));
	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	if (pIP)
		pIP->GetWindowTextA(szIP, sizeof(szIP));
	CWnd* pPort = GetDlgItem(IDC_EDIT_Port);
	if (pPort)
		pPort->GetWindowTextA(szPort, sizeof(szPort));

	fprintf(file, "Server = %s\n", szServer);
	fprintf(file, "IP = %s\n", szIP);
	fprintf(file, "Port = %s\n", szPort);
	fprintf(file, "\n");
/*	fprintf(file, "Adapter = %s\n", m_socketData.szAdapter);
	fprintf(file, "Display = %s\n", m_socketData.szDisplay);
	fprintf(file, "DrvVersion = %s\n", m_socketData.szDrvVersion);
	fprintf(file, "Host = %s\n", m_socketData.szHostName);
	fprintf(file, "xResolution = %d\n", m_socketData.displaySetting.nXResolution);
	fprintf(file, "yResolution = %d\n", m_socketData.displaySetting.nYResolution);
	fprintf(file, "ColorDepth = %d\n", m_socketData.displaySetting.nColourDepth);
	fprintf(file, "RefreshRate = %f\n", m_socketData.displaySetting.fRefreshRate);
    fprintf(file, "Brightness = %d\n", m_socketData.displaySetting.nBrightness);
    fprintf(file, "Contrast = %d\n", m_socketData.displaySetting.nContrast);
    fprintf(file, "Saturation = %d\n", m_socketData.displaySetting.nSaturation);
    fprintf(file, "Hue = %d\n", m_socketData.displaySetting.nHue);
    fprintf(file, "Temperature = %d\n", m_socketData.displaySetting.nTemperature);

    fprintf(file, "GammaR = ");
    for (int i=0; i<256; i++)
        fprintf(file, "%d,", m_socketData.displaySetting.wGamma[0][i]);
    fprintf(file, "\n");
    fprintf(file, "GammaG = ");
    for (int i=0; i<256; i++)
        fprintf(file, "%d,", m_socketData.displaySetting.wGamma[1][i]);
    fprintf(file, "\n");
    fprintf(file, "GammaB = ");
    for (int i=0; i<256; i++)
        fprintf(file, "%d,", m_socketData.displaySetting.wGamma[2][i]);
    fprintf(file, "\n");

	fprintf(file, "Rate = %d\n", (UINT)m_socketData.displaySetting.rate);*/
	fclose(file);
	return true;
}

bool CCatalystMonitorClientDlg::LoadAllSettings(char* pszServer)
{
	CString strFile = GetModulePath();
	strFile.Append(s_szIniFile);
	FILE* file = fopen(strFile, "r");
	if (file == NULL)
		return false;
	
	char szFlag[256] = "";
	fgets(szFlag, sizeof(szFlag), file);
	if (strstr(szFlag, s_szVPPClientFlag) != szFlag)
	{
		fclose(file);
		return false;
	}

	char szTemp[2048] = "";
	while (fgets(szTemp, sizeof(szTemp), file) != NULL)
	{
		if (strstr(szTemp, "Server = ") == szTemp)
		{
			strcpy(pszServer, szTemp+9);
			pszServer[strlen(pszServer)-1] = '\0';
		}
		else if(strstr(szTemp, "IP = ") == szTemp)
		{
			char szIP[256] = "";
			sscanf(szTemp, "IP = %s\n", szIP);
			m_nIP = inet_addr(szIP);
		}
		else if(strstr(szTemp, "Port = ") == szTemp)
			sscanf(szTemp, "Port = %d\n", &m_nPort);
/*		else if(strstr(szTemp, "Adapter = ") == szTemp)
		{
			strcpy(m_socketData.szAdapter, szTemp+10); // avoid blank space
			m_socketData.szAdapter[strlen(m_socketData.szAdapter)-1] = '\0';
		}
		else if(strstr(szTemp, "Display = ") == szTemp)
		{
			strcpy(m_socketData.szDisplay, szTemp+10);
			m_socketData.szDisplay[strlen(m_socketData.szDisplay)-1] = '\0';
		}
		else if(strstr(szTemp, "DrvVersion = ") == szTemp)
		{
			strcpy(m_socketData.szDrvVersion, szTemp+13);
			m_socketData.szDrvVersion[strlen(m_socketData.szDrvVersion)-1] = '\0';
		}
		else if(strstr(szTemp, "Host = ") == szTemp)
		{
			strcpy(m_socketData.szHostName, szTemp+7);
			m_socketData.szHostName[strlen(m_socketData.szHostName)-1] = '\0';
		}
		else if(strstr(szTemp, "xResolution = ") == szTemp)
			sscanf(szTemp, "xResolution = %d\n", &m_socketData.displaySetting.nXResolution);
		else if(strstr(szTemp, "yResolution = ") == szTemp)
			sscanf(szTemp, "yResolution = %d\n", &m_socketData.displaySetting.nYResolution);
		else if(strstr(szTemp, "ColorDepth = ") == szTemp)
			sscanf(szTemp, "ColorDepth = %d\n", &m_socketData.displaySetting.nColourDepth);
		else if(strstr(szTemp, "RefreshRate = ") == szTemp)
			sscanf(szTemp, "RefreshRate = %f\n", &m_socketData.displaySetting.fRefreshRate);
		else if(strstr(szTemp, "Brightness = ") == szTemp)
            sscanf(szTemp, "Brightness = %d\n", &m_socketData.displaySetting.nBrightness);
		else if(strstr(szTemp, "Contrast = ") == szTemp)
            sscanf(szTemp, "Contrast = %d\n", &m_socketData.displaySetting.nContrast);
		else if(strstr(szTemp, "Saturation = ") == szTemp)
            sscanf(szTemp, "Saturation = %d\n", &m_socketData.displaySetting.nSaturation);
		else if(strstr(szTemp, "Hue = ") == szTemp)
            sscanf(szTemp, "Hue = %d\n", &m_socketData.displaySetting.nHue);
		else if(strstr(szTemp, "Temperature = ") == szTemp)
            sscanf(szTemp, "Temperature = %d\n", &m_socketData.displaySetting.nTemperature);
		else if(strstr(szTemp, "Rate = ") == szTemp)
			sscanf(szTemp, "Rate = %d\n", &m_socketData.displaySetting.rate);
        else if (strstr(szTemp, "GammaR = ") == szTemp)
        {
            sscanf(szTemp, "GammaR = %d", &m_socketData.displaySetting.wGamma[0][0]);
            char* pNumber = szTemp + 10;
            for (int i=1; i<256; i++)
            {
                pNumber = strstr(pNumber, ",");
                pNumber++;
                m_socketData.displaySetting.wGamma[0][i] = atoi(pNumber);
            }
        }
        else if (strstr(szTemp, "GammaG = ") == szTemp)
        {
            sscanf(szTemp, "GammaG = %d", &m_socketData.displaySetting.wGamma[1][0]);
            char* pNumber = szTemp + 10;
            for (int i=1; i<256; i++)
            {
                pNumber = strstr(pNumber, ",");
                pNumber++;
                m_socketData.displaySetting.wGamma[1][i] = atoi(pNumber);
            }
        }
        else if (strstr(szTemp, "GammaB = ") == szTemp)
        {
            sscanf(szTemp, "GammaB = %d", &m_socketData.displaySetting.wGamma[2][0]);
            char* pNumber = szTemp + 10;
            for (int i=1; i<256; i++)
            {
                pNumber = strstr(pNumber, ",");
                pNumber++;
                m_socketData.displaySetting.wGamma[2][i] = atoi(pNumber);
            }
        }*/
		memset(szTemp, 0, sizeof(szTemp));
	}
	fclose(file);
	return true;
}

ULONG CCatalystMonitorClientDlg::GetServerIP(char* host_name)
{
	hostent *phe = gethostbyname(host_name);
	if (phe != 0)
	{
		in_addr addr = {};
		memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
		return addr.s_addr;
		//char* szIP = inet_ntoa(addr);
	}
	else
		return 0;
}

void CCatalystMonitorClientDlg::OnBnClickedRadioServer()
{
	CWnd* pServer = GetDlgItem(IDC_EDIT_Server);
	if (pServer)
		pServer->EnableWindow(TRUE);

	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	if (pIP)
		pIP->EnableWindow(FALSE);
}

void CCatalystMonitorClientDlg::OnBnClickedRadioIp()
{
	CWnd* pServer = GetDlgItem(IDC_EDIT_Server);
	if (pServer)
		pServer->EnableWindow(FALSE);

	CWnd* pIP = GetDlgItem(IDC_EDIT_IP);
	if (pIP)
		pIP->EnableWindow(TRUE);
}

void CCatalystMonitorClientDlg::OnBnClickedButtonClose()
{
	SaveAllSettings();
	if (m_hThread)
	{
		m_bTerminateThread = true;
		WaitForSingleObject(m_hThread, 5000);
		CloseHandle(m_hThread);
	}
	OnOK();
}

void CCatalystMonitorClientDlg::OnClose()
{
	OnBnClickedButtonClose();
}

CString CCatalystMonitorClientDlg::GetModulePath()
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

