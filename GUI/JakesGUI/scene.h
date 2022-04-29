# pragma once 
#include <d2d1.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "d2d1")
#include <assert.h>
#include <shobjidl.h>



class GraphicsScene
{
    protected:
        ID2D1Factory *m_pFactory;
        ID2D1HwndRenderTarget *m_pRenderTarget;

        float m_fScaleX
};