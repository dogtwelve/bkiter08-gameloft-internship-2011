#ifndef __CCOORDINATECONVERTER_H__
#define __CCOORDINATECONVERTER_H__

#include "SGraphics.h"
#include "CVSView.h"
#include "CImage.h"

using namespace GameTutor;

class CCoordinateConverter
{
public:
	static void WindowsToOpenGL(SPosition2D<__INT32> winPos, SPosition2D<float> & oglPos)
	{
		__INT32 w = CVSView::GetInstance()->GetWidth();
		__INT32 h = CVSView::GetInstance()->GetHeight();

		oglPos.X = winPos.X * 2.0f / w - 1.0f;
		oglPos.Y = 1.0f - (h - winPos.Y) * 2.0f / h;
	}

	static void WindowsToOpenGL(SRect<__INT32> winRect, SRect<float> & oglRect)
	{
		__INT32 w = CVSView::GetInstance()->GetWidth();
		__INT32 h = CVSView::GetInstance()->GetHeight();

		oglRect.X = winRect.X * 2.0f / w - 1.0f;
		oglRect.Y = 1.0f - (h - winRect.Y) * 2.0f / h;
		oglRect.W = winRect.W * 2.0f / w;
		oglRect.H = winRect.H * 2.0f / h;
	}

	static void NormalizeImageCoords(SRect<__INT32> rect, SRect<float> & norm, CImage* img)
	{
		__INT32 w = img->GetWidth();
		__INT32 h = img->GetHeight();

		norm.X = (float) rect.X / w;
		norm.Y = (float) rect.Y / h;
		norm.W = (float) rect.W / w;
		norm.H = (float) rect.H / h;
	}
};

#endif