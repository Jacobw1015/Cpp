#include "common.h"





struct Lines
{
    D2D1_POINT_2F point1,point2;
    void Draw(ID2D1RenderTarget *pRT, ID2D1SolidColorBrush *pBrush)
    {
       pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
        pRT->DrawLine(point1,point2,pBrush,1.0f);
    };

    
};