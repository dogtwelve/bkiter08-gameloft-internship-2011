#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

class Model
{
public:
	Model(void);
	Model(float* buffer, int numFaces);
	virtual ~Model(void);
	void Render();

	float* GetBuffer();
	int GetNumFaces() { return m_iNumFaces; }
	/* static methods */
	static Model* LoadObjModel(const char* strModelName);	

private:
	int m_iNumFaces;
	float *m_afBuffer;
};

#endif