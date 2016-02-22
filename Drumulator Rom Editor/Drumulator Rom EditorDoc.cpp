// Drumulator Rom EditorDoc.cpp : implementation of the CDrumulatorRomEditorDoc class
//

#include "stdafx.h"
#include "Drumulator Rom Editor.h"
#include "Drumulator Rom EditorDoc.h"
#include "marker_api.h"
#include "wavapi.h"
#include "assignsound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrumulatorRomEditorDoc

IMPLEMENT_DYNCREATE(CDrumulatorRomEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrumulatorRomEditorDoc, CDocument)
END_MESSAGE_MAP()


// CDrumulatorRomEditorDoc construction/destruction

CDrumulatorRomEditorDoc::CDrumulatorRomEditorDoc()
{
	// TODO: add one-time construction code here

}

CDrumulatorRomEditorDoc::~CDrumulatorRomEditorDoc()
{
}

BOOL CDrumulatorRomEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDrumulatorRomEditorDoc serialization

void CDrumulatorRomEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CDrumulatorRomEditorDoc diagnostics

#ifdef _DEBUG
void CDrumulatorRomEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrumulatorRomEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrumulatorRomEditorDoc commands
BOOL CDrumulatorRomEditorDoc::OnOpenDocument(LPCTSTR lpszMarkerPathName)
{
	CStdioFile markerfile;
	CFile waverom;
	CFile wavefile;
	CFileException fe;
	size_t stringsize;
	const wchar_t *pstring;

	/* Create the filename for the corresponding wavefile */
	stringsize = _tcslen(lpszMarkerPathName);
	LPCWSTR lpszWavePathName = new TCHAR[ stringsize + 1];
	LPCWSTR	lpszWaveRomPathName = new TCHAR[ stringsize +1];
	lpszRomPathName = new TCHAR[ stringsize + 5];

	_tcscpy((wchar_t *)lpszWavePathName, (wchar_t *)lpszMarkerPathName);
	_tcscpy((wchar_t *)lpszRomPathName, (wchar_t *)lpszMarkerPathName);
	_tcscpy((wchar_t *)lpszWaveRomPathName, (wchar_t *)lpszMarkerPathName);

	pstring = wcsrchr(lpszWavePathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(".wav"));
	pstring = wcsrchr(lpszRomPathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(" ROM.bin"));
	pstring = wcsrchr(lpszWaveRomPathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(".bin"));

	/* Check if markerfile is readable */
	if (!markerfile.Open(lpszMarkerPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		ReportSaveLoadException(lpszMarkerPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	/* Check if wavefile is readable */
	if (!wavefile.Open(lpszWavePathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		ReportSaveLoadException(lpszWavePathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	/* Check if there is a waverom file */
	if (!waverom.Open(lpszWaveRomPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{

	}
	
	DeleteContents();
	BeginWaitCursor();
	TRY
	{
		::ReadMarkerFile(markerfile);
		m_hWav = ::ReadWAVFile(lpszWavePathName);
		::SplitWaveRom(waverom, lpszWaveRomPathName);
	}
	CATCH (CFileException, eLoad)
	{
		markerfile.Abort(); // will not throw an exception
		wavefile.Abort(); // will not throw an exception
		waverom.Abort();

		EndWaitCursor();
		ReportSaveLoadException(lpszMarkerPathName, eLoad,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		ReportSaveLoadException(lpszWavePathName, eLoad,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		ReportSaveLoadException(lpszWaveRomPathName, eLoad,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);

		m_hMarkerFile = NULL;
		return FALSE;
	}
	END_CATCH

//	InitWAVData();
	EndWaitCursor();

	if (m_hMarkerFile == NULL)
	{
		return FALSE;
	}

	SetPathName(lpszRomPathName);
	SetModifiedFlag(FALSE);     // start off with unmodified

	CAssignSound	AssignSound;
	AssignSound.DoModal();

	return TRUE;
}
