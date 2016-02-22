// Drumulator Rom EditorView.h : interface of the CDrumulatorRomEditorView class
//


#pragma once


class CDrumulatorRomEditorView : public CView
{
protected: // create from serialization only
	CDrumulatorRomEditorView();
	DECLARE_DYNCREATE(CDrumulatorRomEditorView)

// Attributes
public:
	CDrumulatorRomEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CDrumulatorRomEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Drumulator Rom EditorView.cpp
inline CDrumulatorRomEditorDoc* CDrumulatorRomEditorView::GetDocument() const
   { return reinterpret_cast<CDrumulatorRomEditorDoc*>(m_pDocument); }
#endif

