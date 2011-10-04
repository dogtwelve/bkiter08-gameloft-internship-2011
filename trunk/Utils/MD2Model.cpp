#include "MD2Model.h"

extern UserData *userData;

MD2Model::MD2Model(void)
{
	
}


MD2Model::~MD2Model(void)
{
	delete[] m_TexCoords;
	delete[] m_Triangles;

	for(int i = 0; i < m_Header.numFrames; i++) 
	{
		delete[] m_Frames[i].verts;
	}
	delete[] m_Frames;

	delete[] m_afVertexBuffer;
	delete[] m_afTexCoordBuffer;
	delete[] m_TextureData;
}

void MD2Model::LoadModel(const char* strModelName)
{

	FILE* f;
	f = fopen(strModelName, "rb");

	if(f == NULL) 
	{
		printf("Can't read %s file\n", strModelName);
		return;
	}

	fread(&m_Header, sizeof(sMD2Header), 1, f);

	if(m_Header.id != MD2_MAGIC_NUMBER || m_Header.version != 8) 
	{
		printf("This isn't MD2 file\n");
		return;
	}

	// allocate memory
	m_Frames = new sMD2Frame[m_Header.numFrames];
	for(int i = 0; i < m_Header.numFrames; i++) 
	{
		m_Frames[i].verts = new sMD2Vertex[m_Header.numVertices];
	}
	m_TexCoords = new sMD2TexCoord[m_Header.numTexCoords];
	m_Triangles = new sMD2Triangle[m_Header.numTriangles];

	m_afVertexBuffer = new float[9 * m_Header.numFrames * m_Header.numTriangles];
	m_afTexCoordBuffer = new float[6 * m_Header.numFrames * m_Header.numTriangles];

	// texture's name
	fseek(f, m_Header.offSkins, SEEK_SET);
	fread(m_strName, 1, 64, f);

	// read triangles
	fseek(f, m_Header.offTriangles, SEEK_SET);
	fread(&m_Triangles[0], sizeof(sMD2Triangle), m_Header.numTriangles, f);

	// read texture's coordinates
	fseek(f, m_Header.offTexCoord, SEEK_SET);
	fread(&m_TexCoords[0], sizeof(sMD2TexCoord), m_Header.numTexCoords, f); 

	// read frame
	fseek(f, m_Header.offFrames, SEEK_SET);
	for(int i = 0; i < m_Header.numFrames; i++) 
	{
		fread(&m_Frames[i], sizeof(sMD2Frame) - sizeof(sMD2Vertex*), 1, f);
		fread(m_Frames[i].verts, sizeof(sMD2Vertex), m_Header.numVertices, f);
	}

	// normalize coords
	RebuildCoords();

	fclose(f);
}

void MD2Model::Render(int frameIndex)
{
	glBindTexture(GL_TEXTURE_2D, m_iTexID);
	glUniform1f(userData->u_texture, 0);

	glVertexAttribPointer(userData->iVerticesLoc, 
		3, GL_FLOAT, GL_FALSE, 0, m_afVertexBuffer + frameIndex * 9 * m_Header.numTriangles);
	glVertexAttribPointer(userData->iUV, 
		2, GL_FLOAT, GL_FALSE, 0, m_afTexCoordBuffer + frameIndex * 6 * m_Header.numTriangles);
	glDrawArrays(GL_TRIANGLES, 0, 3 * m_Header.numTriangles);
}

void MD2Model::RebuildCoords()
{	
	int vIndex = 0, tIndex = 0;
	sMD2Frame* pFrame;
	sMD2Triangle* pTriangle;
	sMD2Vertex* pVert;

	for(int i = 0; i < m_Header.numFrames; i++) 
	{
		pFrame = &m_Frames[i];
		for(int j = 0; j < m_Header.numTriangles; j++) 
		{
			pTriangle = &m_Triangles[j];
			for(int k = 0; k < 3; k++) // interate each vertex in triangle
			{				
				pVert = &pFrame->verts[pTriangle->vertexIndex[k]];
				m_afVertexBuffer[vIndex++] = pFrame->scale[0] * pVert->v[0] + pFrame->translate[0];
				m_afVertexBuffer[vIndex++] = pFrame->scale[1] * pVert->v[1] + pFrame->translate[1];
				m_afVertexBuffer[vIndex++] = pFrame->scale[2] * pVert->v[2] + pFrame->translate[2] - 200.0f; //TRICK
				
				m_afTexCoordBuffer[tIndex++] = (float) m_TexCoords[pTriangle->textureIndex[k]].s / m_Header.width;
				m_afTexCoordBuffer[tIndex++] = (float) m_TexCoords[pTriangle->textureIndex[k]].t / m_Header.height;
			}
		}
	}
}

void MD2Model::AddTexture(char* strTextureName)
{
	int w, h;
	glGenTextures(1, &m_iTexID);
	m_TextureData = esLoadTGA(strTextureName, &w, &h);

	glBindTexture(GL_TEXTURE_2D, m_iTexID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TextureData);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}