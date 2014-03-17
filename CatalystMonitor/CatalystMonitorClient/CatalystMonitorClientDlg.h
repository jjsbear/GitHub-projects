
// CatalystMonitorClientDlg.h : header file
//

#pragma once
#include "vector"
#include "..\\include\\socket.h"

struct ADLFeatureCaps;
struct ADLFeatureValues;
class CCatalystMonitorClientDlg : public CDialog
{
// Construction
public:
	CCatalystMonitorClientDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCatalystMonitorClientDlg();

// Dialog Data
	enum { IDD = IDD_VPPDISPLAYCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
public:	
    bool m_bConnected;
	bool m_bTerminateThread;

	bool DetectSettingChange();
	bool ConnectionTest(bool bMainThread);
    bool SocketSpeedTest();
    bool SendCatalystSetting();
	void EnableDlgItem(BOOL bEnable);

private:
	ULONG	m_nIP;		// Server's
	u_short m_nPort;	// Server's
	HANDLE	m_hThread;
	SocketDataSend m_socketData;

    int					m_nFeatureCount;
	ADLFeatureCaps*		m_lpFeatureCaps;
	ADLFeatureValues*	m_lpFeatureValues;

	bool SaveAllSettings();
	bool LoadAllSettings(char* pszServer);
	ULONG	GetServerIP(char* host_name);
	CString GetModulePath();

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedRadioServer();
	afx_msg void OnBnClickedRadioIp();
	afx_msg void OnBnClickedButtonClose();
};
