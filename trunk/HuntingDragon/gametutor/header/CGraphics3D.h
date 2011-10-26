#ifndef __CGRAPHICS3D_H__
#define __CGRAPHICS3D_H__

#include "CGLPipelineDriver.h"
#include "SGraphics.h"
#include "CImage.h"
#include "CViewController.h"
#include "CVertex.h"
#include "Matrix.h"

#define EG3D_PIPELINE_MAX_VERTEX_STACK		100000

enum EG3DGLPipelineElementType
{	
	EG3DP_ELETYPE_TRIANGLE,
	EG3DP_ELETYPE_MESH
};

class CGraphics3D:public CSingleton<CGraphics3D>
{
	struct SGraphics3DGLPipelineVertexData
	{
		SPosition3D<float> Pos;
		SPosition2D<float> TexCoor;
	};	

	friend class CSingleton<CGraphics3D>;
protected:
	CGraphics3D()
	{
		m_pVideoDriver = CGLPipelineDriver::GetInstance();
		m_iNumberOfElement = 0;
		m_iStreamOffset = 0;	
	}
	CGLPipelineDriver *m_pVideoDriver;

public:
	void Reset()
	{
		__UINT32 w = (CViewController<CVSView>::GetInstance()->GetView()->GetWidth());
		__UINT32 h = (CViewController<CVSView>::GetInstance()->GetView()->GetHeight());
		Clear(SColor<float>(0, 0, 0, 1));
		m_pVideoDriver->Viewport(SRect<__INT32>(0, 0, w, h));
		m_pVideoDriver->Ortho(0, float(w), 0, float(h) , 0, 1000 );
	}

	void Clear(SColor<float>c)
	{
		m_pVideoDriver->Clear(c);
	}

	void Clear(SColor<__UINT8> c)
	{
		m_pVideoDriver->Clear(SColor<float>(c.Red/255.0f, c.Green/255.0f, c.Blue/255.0f, c.Alpha/255.0f));
	}



	void DrawTriangle(CVertexPT p1, CVertexPT p2, CVertexPT p3, CImage* img) 
	{
		m_Type[m_iNumberOfElement] = EG3DP_ELETYPE_TRIANGLE;

		SGraphics3DGLPipelineVertexData vertex[3]  = {	
			{p1.Pos, p1.TexCoord},
			{p2.Pos, p2.TexCoord},
			{p3.Pos, p3.TexCoord},			
		};

		m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
		m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics3DGLPipelineVertexData)*3);
		m_iNumberOfElement++;
		m_iStreamOffset += 3;
	}	

	void SetMVPMatrix(float* mat)
	{		
		m_pVideoDriver->UniformMatrix(mat);		
	}

	void DrawMesh(float* vBuffer, float* texBuffer, __UINT32 numVertices, CImage* img)
	{
		CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
	
		vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, true);
		vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
		vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, false);
		vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, true);	

		Matrix mat;				

		vd->EnableTexture2D(true);
		vd->BindTexture2D(img->GetTextureID());
		vd->EnableBlending(img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
		vd->AttributePointer(
			EGLPD_ATTRIB_TEXCOOR, 
			2, 
			EGLPD_PRIYTPE_FLOAT, 
			0, 
			texBuffer);
		vd->EnableBlending(false);

		vd->AttributePointer(
			EGLPD_ATTRIB_VERTEX, 
			3,
			EGLPD_PRIYTPE_FLOAT, 
			0, 
			vBuffer);

		vd->DrawElements(EGLPD_RENDERMODE_TRIANGLE, numVertices);
	}

	void Flush() 
	{
		CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
		__UINT8 * bstream = (__UINT8 *)(m_pStream);
		__UINT32 stride = sizeof(SGraphics3DGLPipelineVertexData);
		BREAK_IF(m_iNumberOfElement >= EG3D_PIPELINE_MAX_VERTEX_STACK, "m_iNumberOfElement is out of range");
	
		vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, true);
		vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
		vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, false);
		vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, true);		

		int numVertex = 3;
		for (int i = 0; i < m_iNumberOfElement; i++)
		{				
			switch (m_Type[i])
			{			
			case EG3DP_ELETYPE_TRIANGLE:			
				vd->EnableTexture2D(true);
				vd->BindTexture2D(m_pTextureID[i]);
				vd->AttributePointer(
					EGLPD_ATTRIB_TEXCOOR, 
					2, 
					EGLPD_PRIYTPE_FLOAT, 
					stride, 
					bstream + sizeof(SPosition3D<float>));
				numVertex = 3;
				break;
			}

			vd->EnableBlending(m_pIsUseAlpha[i]);
			vd->AttributePointer(
				EGLPD_ATTRIB_VERTEX, 
				3,
				EGLPD_PRIYTPE_FLOAT, 
				stride, 
				bstream);

			vd->DrawElements(EGLPD_RENDERMODE_TRIANGLESTRIP, numVertex);
			bstream += stride*numVertex;
		}

		
		m_iNumberOfElement = 0;
		m_iStreamOffset = 0;
	}

protected:
	int m_iNumberOfElement;
	int m_iStreamOffset;
	__UINT32 m_pTextureID[EG3D_PIPELINE_MAX_VERTEX_STACK];
	bool m_pIsUseAlpha[EG3D_PIPELINE_MAX_VERTEX_STACK];
	SGraphics3DGLPipelineVertexData m_pStream[EG3D_PIPELINE_MAX_VERTEX_STACK];
	enum EG3DGLPipelineElementType m_Type[EG3D_PIPELINE_MAX_VERTEX_STACK];
};

#endif