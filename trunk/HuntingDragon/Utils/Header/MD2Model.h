#pragma once
#ifndef __MD2MODEL_H__
#define __MD2MODEL_H__

#include <stdio.h>
#include "esUtil.h"
#include "Utils.h"
#include "Defs.h"
#include "Image.h"

#define MD2_MAGIC_NUMBER (('2' << 24) | ('P' << 16) | ('D' << 8) | ('I'))

//typedef float sVec3[3];

typedef struct
{
	int id;
	int version;
	int width; // width of texture
	int height; // height of texture
	int frameSize;
	int numTextures;
	int numVertices; // number of vertices/ frame
	int numTexCoords;
	int numTriangles;
	int numGLCmds;
	int numFrames;
	int offSkins; // offset to skin's name
	int offTexCoord;
	int offTriangles;
	int offFrames;
	int offGLCmds;
	int offEnd;
} sMD2Header;

typedef struct 
{
	short s;
	short t;
} sMD2TexCoord;

typedef struct
{
	short vertexIndex[3];
	short textureIndex[3];
} sMD2Triangle;

typedef struct
{
	unsigned char v[3];
	unsigned char normalIndex;
} sMD2Vertex;

typedef struct 
{
	float scale[3];
	float translate[3];
	char name[16];
	sMD2Vertex* verts; // list of frame's vertices
} sMD2Frame;

class MD2Model
{
public:
	MD2Model(void);
	virtual ~MD2Model(void);

	void LoadModel(const char* strModelName);
	void Render(int frameIndex);
	void AddTexture(char* strTextureName);
	int GetNumFrames() { return m_Header.numFrames; }

private:
	void RebuildCoords(); // rebuild to suitable with opengles

private:
	unsigned int m_iTexID;
	char m_strName[64];
	sMD2Header m_Header;
	sMD2Frame* m_Frames;
	sMD2TexCoord* m_TexCoords;
	sMD2Triangle* m_Triangles;

	// buffer to render
	float* m_afVertexBuffer;
	float* m_afTexCoordBuffer;
	unsigned char* m_TextureData;
	int m_TexDataMode; // GL_RGBA or GL_RGB
	TgaInfo* m_TGAImg;
};

#endif