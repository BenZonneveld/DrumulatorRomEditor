// Drumulator Rom EditorView.cpp : implementation of the CDrumulatorRomEditorView class
//

#include "stdafx.h"
#include "Drumulator Rom Editor.h"

#include "Drumulator Rom EditorDoc.h"
#include "Drumulator Rom EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrumulatorRomEditorView

IMPLEMENT_DYNCREATE(CDrumulatorRomEditorView, CView)

BEGIN_MESSAGE_MAP(CDrumulatorRomEditorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDrumulatorRomEditorView construction/destruction

CDrumulatorRomEditorView::CDrumulatorRomEditorView()
{
	// TODO: add construction code here

}

CDrumulatorRomEditorView::~CDrumulatorRomEditorView()
{
}

BOOL CDrumulatorRomEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDrumulatorRomEditorView drawing

void CDrumulatorRomEditorView::OnDraw(CDC* /*pDC*/)
{
	CDrumulatorRomEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

// CDrumulatorRomEditorView diagnostics

#ifdef _DEBUG
void CDrumulatorRomEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CDrumulatorRomEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrumulatorRomEditorDoc* CDrumulatorRomEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrumulatorRomEditorDoc)));
	return (CDrumulatorRomEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrumulatorRomEditorView message handlers
