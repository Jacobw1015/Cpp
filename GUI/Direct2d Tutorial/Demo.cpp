

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

// Direct2D imports
#include <d2d1.h>
#pragma comment(lib,"d2d1")
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do { if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}}while(0)
#else
#define Assert(b)
#endif // Ending for DEBUG/_DEBUG
#endif


#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceRelease)
{
    if(*ppInterfaceRelease ==NULL)
    {
        (*ppInterfaceRelease)->Release();
        (*ppInterfaceRelease) = NULL;
    }
}

class DemoApp
{
    public:
     DemoApp();
     ~DemoApp();

     HRESULT Initialize();

     void RunMessageLoop();

    private: 
     //Device Independant
     HRESULT CreateDIPResources();
    //Device Dependant
     HRESULT CreateDeviceResources();

     // Dicards Resources
     void DiscardDeviceResources();

     HRESULT OnRender();

     void OnResize(UINT width, UINT height);

     static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    private: 
     HWND                   m_hwnd;
     ID2D1Factory*          m_pDirect2dFactory;
     ID2D1HwndRenderTarget* m_pRenderTarget;
     ID2D1SolidColorBrush*  m_pLightGrayBrush;
     ID2D1SolidColorBrush*  m_pCornFlowerBlueBrush;
};
//Constructor
DemoApp::DemoApp():
m_hwnd(NULL),
m_pDirect2dFactory(NULL),
m_pRenderTarget(NULL),
m_pLightGrayBrush(NULL),
m_pCornFlowerBlueBrush(NULL){}

// Destructor
DemoApp::~DemoApp()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightGrayBrush);
    SafeRelease(&m_pCornFlowerBlueBrush);
}

void DemoApp::RunMessageLoop()
{
    MSG msg;
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HRESULT DemoApp::Initialize()
{
    HRESULT hr;

    hr = CreateDIPResources();
    if(SUCCEEDED(hr))
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX)};
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = DemoApp::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        wc.lpszClassName = L"D2DDemoApp";
        RegisterClassEx(&wc);

        FLOAT dpiX,dpiY;
        // Gets system's DPI for proper scaling
        m_pDirect2dFactory->GetDesktopDpi(&dpiX,&dpiY);

        m_hwnd = CreateWindow(
            L"D2DDemoApp",
            L"Direct2D Demo App",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
        );

        hr = m_hwnd ? S_OK : E_FAIL;

        if(SUCCEEDED(hr))
        {
            ShowWindow(m_hwnd,SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
        }
        
    }
    return hr;
}

HRESULT DemoApp::CreateDIPResources()
{
    HRESULT hr = S_OK;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_pDirect2dFactory);

    return hr;
}

HRESULT DemoApp::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if(!m_pRenderTarget) { 
    RECT rc;
    GetClientRect(m_hwnd,&rc);

    D2D1_SIZE_U size = D2D1::SizeU((rc.right-rc.left),(rc.bottom-rc.top));


    hr = m_pDirect2dFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd,size),
        &m_pRenderTarget
    );
     if(SUCCEEDED(hr))
     {
        // Gray Brush
         hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray),
        &m_pLightGrayBrush);
     }
     if(SUCCEEDED(hr))
     {
         hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
         &m_pCornFlowerBlueBrush);
     }
  }
  return hr;

}


void DemoApp::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightGrayBrush);
    SafeRelease(&m_pCornFlowerBlueBrush);
}

LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    if(uMsg==WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        DemoApp *pDemoApp = (DemoApp*)pcs->lpCreateParams;
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pDemoApp)
        );
        result = 1;
    }
    else{
        DemoApp* pDemoApp= reinterpret_cast<DemoApp*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(hwnd,GWLP_USERDATA)
        ));
        bool wasHandled = false;
        if(pDemoApp)
        {
            switch(uMsg)
            {
                case WM_SIZE:
                 {
                     UINT width = LOWORD(lParam);
                     UINT height = HIWORD(lParam);
                     pDemoApp->OnResize(width,height);
                 }
                 result =0;
                 wasHandled = true;
                 break;
                 case WM_DISPLAYCHANGE:
                  {
                      InvalidateRect(hwnd,NULL,FALSE);
                  }
                  result = 0;
                  wasHandled = true;
                  break;
                 case WM_PAINT:
                  {
                      pDemoApp->OnRender();
                      ValidateRect(hwnd,NULL);
                  }
                  result = 0;
                  wasHandled = true;
                  break;
                 case WM_DESTROY:
                  {
                      PostQuitMessage(0);
                  }
                  result = 1; 
                  wasHandled = true;
                  break;
            }
        }

        if(!wasHandled){
            result = DefWindowProc(hwnd,uMsg,wParam,lParam);
        }
    }
    return result;
}

HRESULT DemoApp::OnRender()
{
    HRESULT hr = S_OK;

    hr = CreateDeviceResources();
    if(SUCCEEDED(hr))
    {
        m_pRenderTarget->BeginDraw();

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        /* Following Code creates grid in window */
        D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
        
        int width  = static_cast<int>(rtSize.width);
        int height  = static_cast<int>(rtSize.height);

        // Draw Vertical Lines of grid
        for(int y=0; y < height; y+=15 /* if Rhs number decreases, more squares. Higher number, less squares*/)
        {
            m_pRenderTarget->DrawLine(
                D2D1::Point2F(0.0f,static_cast<FLOAT>(y)),
                D2D1::Point2F(rtSize.width,static_cast<FLOAT>(y)),
                m_pLightGrayBrush,
                0.5f
            );
        }
        // Draw Horizontal Lines of grid
        for(int x = 0; x< width; x+=15 /* if Rhs number decreases, more squares. Higher number, less squares*/)
        {
            m_pRenderTarget->DrawLine(
                D2D1::Point2F(static_cast<FLOAT>(x),0.0f),
                D2D1::Point2F(static_cast<FLOAT>(x),rtSize.height),
                m_pLightGrayBrush,
                0.5f
            );
        }

        D2D1_RECT_F rectangle1 = D2D1::RectF(
            rtSize.width/2  -  50.0f,
            rtSize.height/2 -  20.0f,
            rtSize.width/2  +  50.0f,
            rtSize.height/2 +  20.0f
        );
        D2D1_RECT_F rectangle2 = D2D1::RectF(
            rtSize.width/2 -  100.0f,
            rtSize.height/2 - 100.0f,
            rtSize.width/2 +  100.0f,
            rtSize.height/2 + 100.0f
        );

        m_pRenderTarget->FillRectangle(&rectangle1,m_pLightGrayBrush);
        m_pRenderTarget->DrawRectangle(&rectangle2,m_pCornFlowerBlueBrush);

        hr = m_pRenderTarget->EndDraw();
        if(hr == D2DERR_RECREATE_TARGET)
        {
            hr=S_OK;
            DiscardDeviceResources();
        }
    }
    return hr;
}

void DemoApp::OnResize(UINT width, UINT height)
{
    if(m_pRenderTarget)
    {
        m_pRenderTarget->Resize(D2D1::SizeU(width,height));
    }
}