// Drumulator Rom EditorDoc.h : interface of the CDrumulatorRomEditorDoc class
//

#pragma once

#include "marker_api.h"
#include "wavapi.h"

class CDrumulatorRomEditorDoc : public CDocument
{
protected: // create from serialization only
	CDrumulatorRomEditorDoc();
	DECLARE_DYNCREATE(CDrumulatorRomEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	MWAV GetMWAV() const
		{ return m_hWav; }
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CDrumulatorRomEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MMARKER	m_hMarkerFile;
	MWAV	m_hWav;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
};


