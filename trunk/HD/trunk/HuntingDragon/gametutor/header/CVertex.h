#ifndef __CVERTEX_H__
#define __CVERTEX_H__

#include "SGraphics.h"

struct CVertexPT
{
	CVertexPT(SPosition3D<float> _pos, SPosition2D<float> _texCoord)
		:Pos(_pos), TexCoord(_texCoord) {}

	CVertexPT(float x, float y, float z, float u, float v) 
		:Pos(x, y, z), TexCoord(u, v) {}

	SPosition3D<float> Pos;
	SPosition2D<float> TexCoord;
};

#endif