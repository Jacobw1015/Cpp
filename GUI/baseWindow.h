#pragma once
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

template<class TYPE>
class BaseWindow
{
    public:
     static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
     {
         //Creates and stores States of window apps
         TYPE *pThis = NULL;
         if(uMsg == WM_NCCREATE)
         {  
             //Creates pointer to get data from structure 
             CREATESTRUCT *pCreate = (CREATESTRUCT*)lParam;
             pThis = (TYPE*)pCreate->lpCreateParams;
             SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)pThis);
            //sets instance handle
             pThis->m_hwnd=hwnd; 
         }
         else
         {  //Get Data pointer from structure
             pThis= (TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
         }
         if(pThis){
             return pThis->HandleMessage(uMsg,wParam,lParam);
         }else{
             return DefWindowProc(hwnd,uMsg,wParam,lParam);
         }
     }
    
     BaseWindow(): m_hwnd(NULL){}

     BOOL Create(
         PCWSTR lpWindowName,
         DWORD dwStyle,
         DWORD dwExStyle = 0,
         int x = CW_USEDEFAULT,
         int y = CW_USEDEFAULT,
         int nWidth = CW_USEDEFAULT,
         int nHeight = CW_USEDEFAULT,
         HWND hWndParent = 0,
         HMENU hMenu =0
     ){
        WNDCLASS wc ={0};
         wc.lpfnWndProc = TYPE::WindowProc;
         wc.hInstance = GetModuleHandle(NULL);
         wc.lpszClassName = ClassName();
         RegisterClass(&wc);

         m_hwnd = CreateWindowEx(
             dwExStyle, ClassName(), lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,GetModuleHandle(NULL),this
         );
         return (m_hwnd? TRUE: FALSE);
     }
     HWND Window() const { return m_hwnd; }
     protected:
      virtual PCWSTR ClassName() const = 0;
      virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)= 0;
      HWND m_hwnd;
};

