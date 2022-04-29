#ifndef UNICODE
#define UNICODE
#endif

#include "Demo.h"
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE, LPSTR, int nCmdShow)
{
    HeapSetInformation(NULL,HeapEnableTerminationOnCorruption,NULL,0);

    if(SUCCEEDED(CoInitialize(NULL)))
    {
        DemoApp app;
        if(SUCCEEDED(app.Initialize()))
        {
            app.RunMessageLoop();
        }
        CoUninitialize();
    }
    return 0;
}