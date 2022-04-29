#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "mainwindow.cpp"


int WINAPI WinMain(HINSTANCE hInstnace, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if(!win.Create(L"Circle",WS_OVERLAPPEDWINDOW,0,0,0,300,180))
  {
    return 0;
  }
  ShowWindow(win.Window(), nCmdShow);
  MSG msg;
  while(GetMessage(&msg, NULL,0,0)>0)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}




