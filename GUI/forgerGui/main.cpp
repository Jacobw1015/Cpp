#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch(uMsg)
  {
      case WM_LBUTTONDOWN:
        {
            wchar_t szFileName[MAX_PATH];
            HINSTANCE hInstance= GetModuleHandle(NULL);

            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd,szFileName,L"The name is: ",MB_OK);
        }
      break;
      case WM_CLOSE:
       DestroyWindow(hwnd);
       break;
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
       return DefWindowProc(hwnd,uMsg,wParam,lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE , LPSTR lpCmdLine, int nCmdShow)
{
    LPCWSTR szClassName = L"myWindowClass";
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    wc.cbSize= sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration failed!",L"ERROR!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        szClassName,
        L"The Title",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,240,120,NULL,NULL,hInstance,NULL
    );
    if(hwnd== NULL)
    {
        MessageBox(NULL, L"Failed to create Window!",L"ERROR!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }
    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0)>0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
    return msg.wParam;
}