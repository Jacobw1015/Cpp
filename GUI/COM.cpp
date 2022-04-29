#ifndef UNICODE
#define UNICODE
#endif



#include <iostream>
#include <windows.h>
#include <shobjidl.h>



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE,LPSTR pCmdLine, int nCmdShow ){
    HRESULT hr= CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if(SUCCEEDED(hr)){
        IFileOpenDialog *pFileOpen;

        hr= CoCreateInstance(CLSID_FileOpenDialog,NULL,CLSCTX_ALL,IID_IFileOpenDialog,reinterpret_cast<void**>(&pFileOpen));

        if(SUCCEEDED(hr)){
            hr = pFileOpen->Show(NULL);

            if(SUCCEEDED(hr)){
                IShellItem *pItem;
                hr=pFileOpen->GetResult(&pItem);
                if(SUCCEEDED(hr)){
                    LPWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH,&pszFilePath);
                    if(SUCCEEDED(hr)){
                        MessageBox(NULL,pszFilePath,L"File Path",MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }

    return 0;
}