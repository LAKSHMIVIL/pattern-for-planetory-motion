// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// patternView.cpp : implementation of the CpatternView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "pattern.h"
#endif

#include "patternDoc.h"
#include "patternView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpatternView

IMPLEMENT_DYNCREATE(CpatternView, CView)

BEGIN_MESSAGE_MAP(CpatternView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CpatternView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CpatternView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CpatternView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CpatternView::OnButtonResume)
END_MESSAGE_MAP()

// CpatternView construction/destruction

CpatternView::CpatternView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	int x = 400;
	int y = 200;
	int x1 = (300 + 150 *cos(3));
	int y1 = (200 + 150 * sin(3));
}

CpatternView::~CpatternView()
{
}

BOOL CpatternView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CpatternView drawing

void CpatternView::OnDraw(CDC* pDC)
{
	CpatternDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen redPen;
	redPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&redPen);
	pDC->Ellipse(450, 350, 150, 50);
	pDC->Ellipse(400, 300, 200, 100);
	pDC->Ellipse(330, 230, 270, 170);
	pDC->Ellipse( x+10,  y+10,  x-10,  y-10);
	pDC->Ellipse( x1+10,  y1+10, x1-10, y1-10);
	pDC->SelectObject(pOldPen);
	

	// TODO: add draw code for native data here
}


// CpatternView printing


void CpatternView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CpatternView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CpatternView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CpatternView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CpatternView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CpatternView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CpatternView diagnostics

#ifdef _DEBUG
void CpatternView::AssertValid() const
{
	CView::AssertValid();
}

void CpatternView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpatternDoc* CpatternView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpatternDoc)));
	return (CpatternDoc*)m_pDocument;
}
#endif //_DEBUG


// CpatternView message handlers


void CpatternView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread=AfxBeginThread(CpatternView::StartThread, this);

}
void CpatternView::OnButtonStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CpatternView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();

}
UINT CpatternView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CpatternView* pView = (CpatternView*)Param;
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		j = j + 6;

		//MyPoint.x=300+100*cos(j);
		//MyPoint.y=200+100*sin(j);
		pView->x = 300 + 100 * cos(j);
		pView->y = 200 + 100 * sin(j);
		pView->x1 = 300 + 150 * cos(j+3);
		pView->y1 = 200 + 150 * sin(j+3);
		pView->Invalidate();
		Sleep(300);
	}
	return 0;
}
