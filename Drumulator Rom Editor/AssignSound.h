#pragma once
#include "afxwin.h"


// CAssignSound dialog

class CAssignSound : public CDialog
{
	DECLARE_DYNAMIC(CAssignSound)

public:
	CAssignSound(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAssignSound();

// Dialog Data
	enum { IDD = IDD_PADASSIGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox  mComboSound1;
	CComboBox  mOutputCombo1;
	CButton mPlayButton1;
	CComboBox  mComboSound2;
	CComboBox  mOutputCombo2;
	CButton mPlayButton2;
	CComboBox  mComboSound3;
	CComboBox  mOutputCombo3;
	CButton mPlayButton3;
	CComboBox  mComboSound4;
	CComboBox mOutputCombo4;
	CButton mPlayButton4;
	CComboBox mComboSound5;
	CComboBox mOutputCombo5;
	CButton mPlayButton5;
	CComboBox mComboSound6;
	CComboBox mOutputCombo6;
	CButton mPlayButton6;
	CComboBox mComboSound7;
	CComboBox mOutputCombo7;
	CButton mPlayButton7;
	CComboBox mComboSound8;
	CComboBox mOutputCombo8;
	CButton mPlayButton8;
	CComboBox mComboSound9;
	CComboBox mOutputCombo9;
	CButton mPlayButton9;
	CComboBox mComboSound10;
	CComboBox mOutputCombo10;
	CButton mPlayButton10;
	CComboBox mComboSound11;
	CComboBox mOutputCombo11;
	CButton mPlayButton11;
	CComboBox mComboSound12;
	CComboBox mOutputCombo12;
	CButton mPlayButton12;
	afx_msg void OnBnClickedPlay1();
	afx_msg void OnBnClickedPlay2();
	afx_msg void OnBnClickedPlay3();
	afx_msg void OnBnClickedPlay4();
	afx_msg void OnBnClickedPlay5();
	afx_msg void OnBnClickedPlay6();
	afx_msg void OnBnClickedPlay7();
	afx_msg void OnBnClickedPlay8();
	afx_msg void OnBnClickedPlay9();
	afx_msg void OnBnClickedPlay10();
	afx_msg void OnBnClickedPlay11();
	afx_msg void OnBnClickedPlay12();
	afx_msg void OnBnClickedOkButton();
	afx_msg void OnBnClickedCancel();
};
