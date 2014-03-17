
// CatalystMonitorServerDlg.h : header file
//

#pragma once

#include <vector>
#include "..\\include\\socket.h"

// CCatalystMonitorServerDlg dialog
class CCatalystMonitorServerDlg : public CDialog
{
// Construction
public:
	CCatalystMonitorServerDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCatalystMonitorServerDlg();

// Dialog Data
	enum { IDD = IDD_CatalystMonitorServer_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
public:
	bool m_bTerminateThread;
	bool CreateClientSocket(SOCKET& clientSocket);
	bool AddOneSetting(SocketFeatureData socketData);
	bool RecordService(SocketFeatureData& socketData);

private:
	HANDLE m_hThread;
	SOCKET m_socketServer;

	void CreateServerSocket();
	bool InitializeService();
	void UpdateLocalHostIP();
	bool SaveDisplayListToFile();
	bool LoadDisplayListFromFile();
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
	afx_msg void OnBnClickedButtonService();
	afx_msg void OnBnClickedButtonClose();
};
