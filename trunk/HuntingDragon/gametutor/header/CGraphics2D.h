#ifndef __CGRAPHICS2D_H__
#define __CGRAPHICS2D_H__

#include "CGLPipelineDriver.h"
#include "SGraphics.h"
#include "CImage.h"
#include "CCoordinateConverter.h"
#include "CViewController.h"
#include "CVertex.h"

#define EG2D_PIPELINE_MAX_VERTEX_STACK		1000

enum EG2DGLPipelineElementType
{
	EG2DP_ELETYPE_LINE,
	EG2DP_ELETYPE_TRIANGLE,
	EG2DP_ELETYPE_RECT,
	EG2DP_ELETYPE_IMG,
};

class CGraphics2D:public CSingleton<CGraphics2D>
{
	struct SGraphics2DGLPipelineVertexData
	{
		SPosition2D<float> Pos;
		SColor<float> Color;
		SPosition2D<float> TexCoor;
	};

	struct SGraphics3DGLPipelineVertexData
	{
		SPosition3D<float> Pos;
		SColor<float> Color;
		SPosition2D<float> TexCoor;
	};

	friend class CSingleton<CGraphics2D>;
protected:
	CGraphics2D()
	{
		m_pVideoDriver = CGLPipelineDriver::GetInstance();
		m_iNumberOfElement = 0;
		m_iStreamOffset = 0;
		m_Color = SColor<float>(0.0, 0.0, 0.0, 1.0);
	}
	CGLPipelineDriver *m_pVideoDriver;

public:
	void Reset()
	{
		__UINT32 w = (CViewController<CVSView>::GetInstance()->GetView()->GetWidth());
		__UINT32 h = (CViewController<CVSView>::GetInstance()->GetView()->GetHeight());
		Clear(SColor<float>(0, 0, 0, 1));
		m_pVideoDriver->Viewport(SRect<__INT32>(0, 0, w, h));
		//m_pVideoDriver->LoadIdentity(EGLPD_MATRIXMODE_PROJECTION);
		m_pVideoDriver->Ortho(0, float(w), 0, float(h) , 0, 1000 );

		m_pVideoDriver->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, false);
		m_pVideoDriver->EnableAttribPointer(EGLPD_ATTRIB_COLOR, false);
		m_pVideoDriver->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
		m_pVideoDriver->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, false);
	}

	void Clear(SColor<float>c)
	{
		m_pVideoDriver->Clear(c);
	}

	void Clear(SColor<__UINT8> c)
	{
		m_pVideoDriver->Clear(SColor<float>(c.Red/255.0f, c.Green/255.0f, c.Blue/255.0f, c.Alpha/255.0f));
	}

	void SetColor(SColor<float> c) 
	{
		memcpy(&m_Color, &c, sizeof(m_Color));
	}
	void SetColor(SColor<__UINT8> c) 
	{
		m_Color.Alpha = c.Alpha/255.0f;
		m_Color.Blue = c.Blue/255.0f;
		m_Color.Green = c.Green/255.0f;
		m_Color.Red = c.Red/255.0f;
	}

	void DrawRect(SRect<float> rect) 
	{
		TODO("DrawRect is not implemented");
	}

	void DrawRect(SRect<__INT32> rect) 
	{
		TODO("DrawRect is not implemented");
	}

	void DrawLine(SPosition2D<float> startpoint, SPosition2D<float> endpoint) 
	{
		TODO("DrawLine is not implemented");
	}

	void DrawLine(SPosition2D<__INT32> startpoint, SPosition2D<__INT32> endpoint) 
	{
		TODO("DrawLine is not implemented");
	}

	void DrawTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) 
	{
		TODO("DrawTriangle is not implemented");
	}

	void DrawTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3) 
	{
		TODO("DrawTriangle is not implemented");
	}

	void FillRect(SRect<float> rect)
	{	
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_RECT;

		SGraphics2DGLPipelineVertexData vertex[4]  = {	
			{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(0, 0)}
		};

		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
		m_iNumberOfElement++;
		m_iStreamOffset += 4;
	}

	void FillRect(SRect<__INT32> rect)
	{
		SRect<float> rect2(float(rect.X), float(rect.Y), float(rect.W), float(rect.H));
		FillRect(rect2);
	}

	void FillTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) 
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_TRIANGLE;

		SGraphics2DGLPipelineVertexData vertex[3]  = {	
			{p1, m_Color, SPosition2D<float>(0, 0)},
			{p2, m_Color, SPosition2D<float>(0, 0)},
			{p3, m_Color, SPosition2D<float>(0, 0)}
		};

		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*3);
		m_iNumberOfElement++;
		m_iStreamOffset += 3;
	}

	void FillTriangle(
		SPosition2D<float> p1, SPosition2D<float> t1, 
		SPosition2D<float> p2, SPosition2D<float> t2, 
		SPosition2D<float> p3, SPosition2D<float> t3
		) {

		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_TRIANGLE;

		SGraphics2DGLPipelineVertexData vertex[3]  = {	
			{p1, m_Color, t1},
			{p2, m_Color, t2},
			{p3, m_Color, t3}
		};

		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*3);
		m_iNumberOfElement++;
		m_iStreamOffset += 3;
	}

	void FillTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3) 
	{
		FillTriangle(SPosition2D<float>(float(p1.X), float(p1.Y)), SPosition2D<float>(float(p2.X), float(p2.Y)), SPosition2D<float>(float(p3.X), float(p3.Y)));
	}

	////////// Draw Image //////////////
	void DrawImage(SPosition2D<float> pos, CImage *img)
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

		SRect<float> rect(pos.X, pos.Y, float(img->GetWidth()), float(img->GetHeight()));
		SGraphics2DGLPipelineVertexData vertex[4]  = {	
			{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 1)},
			{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(1, 1)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(1, 0)}
		};
		m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
		m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
		m_iNumberOfElement++;
		m_iStreamOffset += 4;
	}

	void DrawImage(SPosition2D<__INT32> pos, CImage *img)
	{
		SPosition2D<float> oglPos;
		CCoordinateConverter::WindowsToOpenGL(pos, oglPos);
		DrawImage(oglPos, img);
	}

	void DrawImageRegion(SRect<float> border, SRect<float> texCoord, CImage* img)
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

		// [TODO] need to fix here
		SGraphics2DGLPipelineVertexData vertex[4]  = {	
			{SPosition2D<float>(border.X, border.Y + border.H), m_Color, SPosition2D<float>(texCoord.X, texCoord.Y)},
			{SPosition2D<float>(border.X, border.Y), m_Color, SPosition2D<float>(texCoord.X, texCoord.Y  + texCoord.H)},
			{SPosition2D<float>(border.X + border.W, border.Y + border.H), m_Color, SPosition2D<float>(texCoord.X + texCoord.W, texCoord.Y)},
			{SPosition2D<float>(border.X + border.W, border.Y), m_Color, SPosition2D<float>(texCoord.X + texCoord.W, texCoord.Y  + texCoord.H)}
		};
		m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
		m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
		m_iNumberOfElement++;
		m_iStreamOffset += 4;
	}

	void DrawImageRegion(SRect<__INT32> border, SRect<__INT32> texCoord, CImage* img)
	{
		SRect<float> fBorder, fTexCoord;
		CCoordinateConverter::WindowsToOpenGL(border, fBorder);
		CCoordinateConverter::NormalizeImageCoords(texCoord, fTexCoord, img);
		DrawImageRegion(fBorder, fTexCoord, img);
	}

	//void DrawImageRegion(CVertexPT* v1, CVertexPT* v2, CVertexPT* v3, CImage* img) 
	//{
	//	m_Type[m_iNumberOfElement] = EG3DP_ELETYPE_TRIANGLE;

	//	//// [TODO] need to fix here
	//	SGraphics3DGLPipelineVertexData vertex[3]  = {	
	//		{v1->pos, m_Color, v1->texCoord},
	//		{v2->pos, m_Color, v2->texCoord},
	//		{v3->pos, m_Color, v3->texCoord}
	//	};

	//	m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
	//	m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
	//	memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics3DGLPipelineVertexData)*3);

	//	m_iNumberOfElement++;
	//	m_iStreamOffset += 3;
	//}

	void Flush() 
	{
		CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
			__UINT8 * bstream = (__UINT8 *)(m_pStream);
			__UINT32 stride = sizeof(SGraphics2DGLPipelineVertexData);
			BREAK_IF(m_iNumberOfElement >= EG2D_PIPELINE_MAX_VERTEX_STACK, "m_iNumberOfElement is out of range");

			int numVertex = 0;
			for (int i = 0; i < m_iNumberOfElement; i++)
			{				
				switch (m_Type[i])
				{
				case EG2DP_ELETYPE_RECT:
				case EG2DP_ELETYPE_TRIANGLE:
					m_pIsUseAlpha[i] = (m_Color.Alpha != 1);
					vd->EnableTexture2D(false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, false);
					numVertex = 4;
					if (m_Type[i] == EG2DP_ELETYPE_TRIANGLE)
					{
						numVertex = 3;
					}		
					vd->AttributePointer(
						EGLPD_ATTRIB_COLOR, 
						4, 
						EGLPD_PRIYTPE_FLOAT, 
						stride, 
						bstream + sizeof(SPosition2D<float>));
					break;
				case EG2DP_ELETYPE_IMG:
					vd->EnableTexture2D(true);
					vd->SetColor<float>(1, 1, 1, 1);
					vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, true);
					vd->BindTexture2D(m_pTextureID[i]);
					vd->AttributePointer(
						EGLPD_ATTRIB_TEXCOOR, 
						2, 
						EGLPD_PRIYTPE_FLOAT, 
						stride, 
						bstream + sizeof(SPosition2D<float>) + sizeof(SColor<float>));
					numVertex = 4;
					break;	
				}
				
				if (numVertex)
				{
					vd->EnableBlending(m_pIsUseAlpha[i]);
					vd->AttributePointer(
						EGLPD_ATTRIB_VERTEX, 
						2,
						EGLPD_PRIYTPE_FLOAT, 
						stride, 
						bstream);

					float ident[] = {
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1
					};

					vd->UniformMatrix(ident);

					vd->DrawElements(EGLPD_RENDERMODE_TRIANGLESTRIP, numVertex);
					bstream += stride*numVertex;
				}
			}
			m_iNumberOfElement = 0;
			m_iStreamOffset = 0;
	}

protected:
	SColor<float> m_Color;
	int m_iNumberOfElement;
	int m_iStreamOffset;
	__UINT32 m_pTextureID[EG2D_PIPELINE_MAX_VERTEX_STACK];
	bool m_pIsUseAlpha[EG2D_PIPELINE_MAX_VERTEX_STACK];
	SGraphics2DGLPipelineVertexData m_pStream[EG2D_PIPELINE_MAX_VERTEX_STACK];
	enum EG2DGLPipelineElementType m_Type[EG2D_PIPELINE_MAX_VERTEX_STACK];

};

#endif