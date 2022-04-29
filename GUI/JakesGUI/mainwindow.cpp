#pragma once 
#include <windows.h>
#include "baseWindow.h"
#include <d2d1.h>
#include <iostream>
#pragma comment(lib, "d2d1")
#include <assert.h>
#include "saferelease.h"




class MainWindow: public BaseWindow<MainWindow>
{   
  private:
    ID2D1Factory *pFactory;
    ID2D1HwndRenderTarget *pRenderTarget;
    ID2D1SolidColorBrush *pBrush;
    D2D1_ELLIPSE ellipse;

    void CalculateLayout();
    HRESULT CreateGraphicsResources();
    void DiscardGraphicsResources();
    void OnPaint();
    void Resize();

    public:
      PCWSTR ClassName() const { return L"Main Window";}
      LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

      MainWindow(): pFactory(NULL),pRenderTarget(NULL), pBrush(NULL){}
};

void MainWindow::CalculateLayout()
{
  if(pRenderTarget !=NULL)
  {
    D2D1_SIZE_F size = pRenderTarget->GetSize();
    const float x = size.width / 2;
    const float y = size.height / 2;
    const float radius = std::min(x,y);
    ellipse = D2D1::Ellipse(D2D1::Point2F(x,y),radius,radius);
  }
}

HRESULT MainWindow::CreateGraphicsResources()
{
  HRESULT hr = S_OK;
   if(pRenderTarget == NULL)
   {
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
       const D2D1_COLOR_F color = D2D1::ColorF(1.0f,1.0f,0);
       hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
        if(SUCCEEDED(hr))
         {
           CalculateLayout();
         }
     }
   }
   return hr;
}

void MainWindow::DiscardGraphicsResources()
{
  SafeRelease(&pRenderTarget);
  SafeRelease(&pBrush);
}

void MainWindow::OnPaint()
{
  HRESULT hr = CreateGraphicsResources();
  if(SUCCEEDED(hr))
  {
    PAINTSTRUCT ps;
    BeginPaint(m_hwnd,&ps);

    pRenderTarget->BeginDraw();

    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    pRenderTarget->FillEllipse(ellipse, pBrush);

    hr= pRenderTarget->EndDraw();
    if(FAILED(hr)|| hr== D2DERR_RECREATE_TARGET)
    {
      DiscardGraphicsResources();
    }
    EndPaint(m_hwnd, &ps);
  }
}

void MainWindow::Resize()
{
  if(pRenderTarget != NULL)
  {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    pRenderTarget->Resize(size);
    CalculateLayout();
    InvalidateRect(m_hwnd,NULL,FALSE);
  }
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
      case WM_CREATE:
      if(FAILED(D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)
        ))
        {return -1;}
        return 0;

        case WM_LBUTTONDOWN:
        {
          wchar_t szFileName[MAX_PATH];
          HINSTANCE hInstance = GetModuleHandle(NULL);

          GetModuleFileName(hInstance, szFileName, MAX_PATH);
          MessageBox(m_hwnd, szFileName,L"The name is:",MB_OK);
        }
         return 0;
        case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
          PostQuitMessage(0);
          return 0;
        case WM_PAINT:
       OnPaint();
        return 0;   
        case WM_SIZE:
         Resize();
         return 0;
        default:
          return DefWindowProc(m_hwnd,uMsg,wParam,lParam);
    }
    return TRUE;
}