#ifndef UNICODE
#define UNICODE
#endif


#include "common.h"
#include "basewindow.h"
#include <windowsx.h>
#include <winuser.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <cmath>
#include <iostream>
#pragma comment(lib, "d2d1")
#include <list>
#include <memory>
#include "dpiscale.cpp"
#include "lines.cpp"

float DPIScale::scaleX =1.0f;
float DPIScale::scaleY =1.0f;

template<class T> void SafeRelease(T **ppT)
{
    if(*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class MainWindow: public BaseWindow<MainWindow>
{
    private:
    HCURSOR                hCursor;
    ID2D1Factory          *pFactory;
    ID2D1HwndRenderTarget *pRenderTarget;
    ID2D1SolidColorBrush  *pBrush;
    D2D1_POINT_2F          ptMouse;
    Lines                  lines;
    std::list<Lines>       lLines;

    public:
    void InsertLine(float x, float y);
    void OnLButtonDown(int pixelX,int pixelY,DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX,int pixelY,DWORD flags);
    void Resize();
    void OnPaint();
    HRESULT CreateGraphResources();
    void DiscardResources();
    MainWindow() : pFactory(NULL),pRenderTarget(NULL),pBrush(NULL),ptMouse(D2D1::Point2F()){}


    PCWSTR ClassName() const { return L"Game Window"; }
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

};  



HRESULT MainWindow::CreateGraphResources()
{
    HRESULT hr= S_OK;
    if(pRenderTarget==NULL){
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right,rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd,size),
            &pRenderTarget
        );
        if(SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::SlateGray);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
           
        
        }
    }
    return hr;
}

void MainWindow::DiscardResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}



void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphResources();
    if(SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        
        BeginPaint(m_hwnd,&ps);
        pRenderTarget->BeginDraw();
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Beige));
        D2D1_SIZE_F rtSize = pRenderTarget->GetSize();
        
        int width  = static_cast<int>(rtSize.width);
        int height  = static_cast<int>(rtSize.height);
      
        // Draw Vertical Lines of grid
        for(int y=0; y < height; y+=15 /* if Rhs number decreases, more squares. Higher number, less squares*/)
        {
            pRenderTarget->DrawLine(
                D2D1::Point2F(0.0f,static_cast<FLOAT>(y)),
                D2D1::Point2F(rtSize.width,static_cast<FLOAT>(y)),
                pBrush,
                0.5f
            );
        }
        // Draw Horizontal Lines of grid
        for(int x = 0; x< width; x+=15 /* if Rhs number decreases, more squares. Higher number, less squares*/)
        {
            pRenderTarget->DrawLine(
                D2D1::Point2F(static_cast<FLOAT>(x),0.0f),
                D2D1::Point2F(static_cast<FLOAT>(x),rtSize.height),
                pBrush,
                0.5f
            );
        }

        
            lines.Draw(pRenderTarget,pBrush);
        

        
        hr= pRenderTarget->EndDraw();
        if(FAILED(hr))
        {
            hr = S_OK;
            DiscardResources();
        }
        EndPaint(m_hwnd,&ps);
    }
    
}

void MainWindow::OnLButtonDown(int pixelX,int pixelY,DWORD flags)
{
    
    POINT pt = {pixelX,pixelY};
    const float dipX = DPIScale::PixelsToDipsX(pixelX);
    const float dipY = DPIScale::PixelsToDipsY(pixelY);
   if(DragDetect(m_hwnd,pt))
   {
       SetCapture(m_hwnd);
        lines.point1 = ptMouse = D2D1::Point2F(dipX,dipY);
   }
       
  
    InvalidateRect(m_hwnd,NULL,FALSE);
  
}

void MainWindow::OnLButtonUp(){
    
    InvalidateRect(m_hwnd,NULL,FALSE);
    ReleaseCapture();
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    const float dipX = DPIScale::PixelsToDipsX(pixelX);
    const float dipY = DPIScale::PixelsToDipsY(pixelY);

    if(flags & MK_LBUTTON)
    {
  
         lines.point2 = ptMouse = D2D1::Point2F(dipX,dipY);
   
    }
       InvalidateRect(m_hwnd,NULL,FALSE);
  
}


void MainWindow::Resize()
{
    
       if(pRenderTarget !=NULL)
       { 
         RECT rc;
         GetClientRect(m_hwnd,&rc);
         D2D1_SIZE_U size = D2D1::SizeU(rc.right,rc.bottom);

        pRenderTarget->Resize(size);

        InvalidateRect(m_hwnd,NULL,FALSE);
       }
    
}


LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
          if(FAILED(D2D1CreateFactory(
              D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory
          )))
          {
              return -1;
          }
          DPIScale::Initialize(pFactory);
          return 0;
          case WM_PAINT:
           OnPaint();
        return 0;
        case WM_SIZE:
            Resize();
        return 0;
        case WM_DESTROY:
         DiscardResources();
         SafeRelease(&pFactory);
         PostQuitMessage(0);
         return 0;
         case WM_LBUTTONDOWN:
          OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),(DWORD)wParam);
          return 0;
        case WM_LBUTTONUP:
            OnLButtonUp();
            return 0;
        case WM_MOUSEMOVE:
         OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),(DWORD)wParam);
         return 0;
      
    }
    return DefWindowProc(m_hwnd,msg,wParam, lParam);
}