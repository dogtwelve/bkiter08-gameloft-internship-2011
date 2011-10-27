#include "CTerrain.h"

CTerrain::CTerrain()
{
	CReaderStream<CFileWin32Driver> file("grass.tga");
	m_img = CImage::LoadTGA(&file);
	m_img->BindGPU(CGLPipelineDriver::GetInstance());
}

CTerrain::~CTerrain()
{

}

void CTerrain::Render()
{
	CGraphics3D::GetInstance()->DrawRectangle(
		CVertexPT(-X_MAX/2.0f, -Z_MAX/2.0f, -1, 0, 0),
		CVertexPT(-X_MAX/2.0f, Z_MAX/2.0f, -1, 0, 1),
		CVertexPT(X_MAX/2.0f, Z_MAX/2.0f, -1, 1, 1),
		CVertexPT(X_MAX/2.0f, -Z_MAX/2.0f, -1, 1, 0),
		m_img
		);
}