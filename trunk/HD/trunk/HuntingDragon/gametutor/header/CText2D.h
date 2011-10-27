#ifndef __CTEXT2D_H__
#define __CTEXT2D_H__

#include <string.h>
#include "gametutor.h"
#include "CGraphics2D.h"
#include "CGLPipelineDriver.h"
#include "CCharMap.h"

class CText2D	
{
public:
	CText2D();
	CText2D(char* text);
	virtual ~CText2D();

	void SetText(char* text);
	void SetCharmap(unsigned int texId);
	void Render(float posX, float posY);
private:
	char* m_strText;
	unsigned int m_uTexId;
	CGraphics2D* g;
	CImage* m_img;
	CGLPipelineDriver* m_pVideoDriver;
	CCharMap* m_CharMap;
};

#endif