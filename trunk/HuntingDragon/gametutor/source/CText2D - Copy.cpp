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

void CText2D::Render(float posX, float posY)
{
	float x = posX;	
	for(int i = 0; i < strlen(m_strText); i++) 
	{
		SCharMap* map = m_CharMap->GetMap(m_strText[i]);
		if(map != NULL)
		{
			SRect<float> border(x, posY, 1.0f/16.0f, 1.0f/16.0f);
			SRect<float> texCoord(map->x/256.0f, map->y/256.0f, map->w/256.0f, map->h/256.0f);
			g->DrawImage(border, texCoord, m_img);
			x += 1.0f/16.0f;
		}
	}
}

void CText2D::SetCharmap(unsigned int texId)
{
}