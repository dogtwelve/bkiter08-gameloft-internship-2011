#include "CModel.h"

CModel::CModel(void)
{
	m_pVideoDriver = CGLPipelineDriver::GetInstance();
	
	//CReaderStream<CFileWin32Driver> file("dragoon.pcx");
	m_Texture = CImage::LoadPCX("dragoon.pcx");
	m_Texture->BindGPU(m_pVideoDriver);
	g3d = CGraphics3D::GetInstance();
	g3d->Reset();
}


CModel::~CModel(void)
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

void CModel::LoadModel(const char* strModelName)
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

	for(int i = 0; i < m_Header.numFrames; i++) 
	{
		printf("%d: %s\n", i, m_Frames[i].name);
	}
	// normalize coords
	BuildBuffers();

	fclose(f);
}

void CModel::Render(int frameIndex)
{
	g3d->DrawMesh(m_afVertexBuffer + frameIndex * 9 * m_Header.numTriangles, 
		m_afTexCoordBuffer + frameIndex * 6 * m_Header.numTriangles, 
		m_Header.numTriangles * 3, 
		m_Texture);	
}

void CModel::BuildBuffers()
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
			for(int k = 0; k < 3; k++) // iterate each vertex in triangle
			{				
				pVert = &pFrame->verts[pTriangle->vertexIndex[k]];
				m_afVertexBuffer[vIndex++] = pFrame->scale[0] * pVert->v[0] + pFrame->translate[0];
				m_afVertexBuffer[vIndex++] = pFrame->scale[1] * pVert->v[1] + pFrame->translate[1];
				m_afVertexBuffer[vIndex++] = pFrame->scale[2] * pVert->v[2] + pFrame->translate[2];

				//TRICK: scale model
				for(int i = 1; i <= 3; i++)
				{
					m_afVertexBuffer[vIndex-i] /= 100.0f;
					if(m_afVertexBuffer[vIndex-i] > 1 || m_afVertexBuffer[vIndex-i] < -1) 
					{
						printf("%f Error >\"<!\n", m_afVertexBuffer[vIndex-i]);
					}
				}
				//~TRICK
				
				m_afTexCoordBuffer[tIndex++] = (float) m_TexCoords[pTriangle->textureIndex[k]].s / m_Header.width;
				m_afTexCoordBuffer[tIndex++] = 1.0f - (float) m_TexCoords[pTriangle->textureIndex[k]].t / m_Header.height;
			}
		}
	}
}

void CModel::AddTexture(char* strTextureName)
{
	int w, h;
	glGenTextures(1, &m_iTexID);
	glBindTexture(GL_TEXTURE_2D, m_iTexID);

	/*if(String::EndsWith(strTextureName, ".pcx"))
	{
	m_TextureData = Image::LoadPcxImage(strTextureName, &w, &h, &m_TexDataMode);

	} else if(String::EndsWith(strTextureName, ".tga"))
	{
	m_TextureData = Image::LoadTgaImage(strTextureName, &w, &h, &m_TexDataMode);
	}*/
	glTexImage2D(GL_TEXTURE_2D, 
		0, m_TexDataMode, w, h, 0, m_TexDataMode, GL_UNSIGNED_BYTE, m_TextureData);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}