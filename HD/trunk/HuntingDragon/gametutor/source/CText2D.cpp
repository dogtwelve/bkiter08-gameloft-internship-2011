#include "CText2D.h"

CText2D::CText2D()
{
	SetText("");
}

CText2D::CText2D(char* text)
{
	SetText(text);
	m_pVideoDriver = CGLPipelineDriver::GetInstance();
	g = CGraphics2D::GetInstance();
	g->Reset();

	CReaderStream<CFileWin32Driver> file("font.tga");
	m_img = CImage::LoadTGA(&file);
	m_img->BindGPU(m_pVideoDriver);
	m_CharMap = new CCharMap();

	m_CharMap->AddMapFromFile("charmap.txt");
}

CText2D::~CText2D()
{
	delete m_strText;
	delete m_CharMap;
}

void CText2D::SetText(char* text)
{
	m_strText = new char[strlen(text)+1];
	strcpy(m_strText, text);
}

void CText2D::Render(float _posX, float _posY)
{
	__INT32 posX = __INT32 (_posX);
	__INT32 posY = __INT32 (_posY);
	for(int i = 0; i < strlen(m_strText); i++) 
	{
		SCharMap* map = m_CharMap->GetMap(m_strText[i]);
		if(map != NULL)
		{
			SRect<__INT32> border(posX, posY, 30, 30);
			SRect<__INT32> texCoord(map->x, map->y, map->w, map->h);
			g->DrawImageRegion(border, texCoord, m_img);
			posX += 30;
		}
	}
}

void CText2D::SetCharmap(unsigned int texId)
{
}