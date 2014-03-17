
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
	bool AddOneSetting(SocketDataSend socketData);
	bool RecordService(SocketDataSend& socketData);

private:
	HANDLE m_hThread;
	SOCKET m_socketServer;

	typedef std::vector<DisplaySetting> SettingList;
	typedef struct strAdapter
	{
		SettingList settingList;
		char szAdapter[256];
	};
	typedef std::vector<strAdapter> AdapterList;
	typedef struct strDisplay
	{
		AdapterList adapterList;
		char szDisplay[256];
	};
	typedef std::vector<strDisplay> DisplayList;
	DisplayList m_displayList;

	void CreateServerSocket();
	bool InitializeService();
	void UpdateLocalHostIP();
	bool SaveDisplayListToFile();
	bool LoadDisplayListFromFile();
	void ClearDisplayList();
	void ClearOneDisplay(strDisplay& display);
	void ClearOneAdapter(strAdapter& adapter);
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
