#ifndef __CTERRAIN_H__
#define __CTERRAIN_H__

#include "gametutor.h"
#include "CImage.h"
#include "CGraphics2D.h"
#include "CGraphics3D.h"
#include "CGLPipelineDriver.h"
#include "CText2D.h"
#include "CModel.h"
#include "CCharacter.h"
#include "CCoordinateConverter.h"
#include "Header.h"

#define X_MAX 20
#define Z_MAX 20

class CTerrain
{
public:
	CTerrain();
	virtual ~CTerrain();

	void Render();
private:
	int m_Heightmap[X_MAX][Z_MAX][3];
	CImage *m_img;
};

#endif