#include "Model.h"

Model::Model(void)
{
}

Model::Model(float* buffer, int numFaces)
{
	m_afBuffer = new float[numFaces*8*3];
	for(int i = 0; i < numFaces*24; i++) 
	{
		m_afBuffer[i] = buffer[i];
	}
	m_iNumFaces = numFaces;
}

Model::~Model(void)
{
}

Model* Model::LoadObjModel(const char* strModelName)
{
	FILE* f;
	f = fopen(strModelName, "rb");

	int v[3], t[3], n[3];

	if(f == NULL) return NULL;

	float vertices_index[500*3];
	float textures_index[500*2];
	float normals_index[500*3];

	int vIndex = 0, tIndex = 0, nIndex = 0;
	int buf_index = 0;

	char buf[100];	
	float buffer[1000*3*8];

	while(!feof(f)) 
	{
		fgets(buf, 100, f);
		if(strlen(buf) < 1) continue;
		if(buf[0] == 'v') 
		{
			if(buf[1] == 'n') 
			{
				sscanf(buf, "vn %f %f %f", 
					&normals_index[nIndex], &normals_index[nIndex+1], &normals_index[nIndex+2]);
				nIndex += 3;
			} else if(buf[1] == 't') 
			{
				sscanf(buf, "vt %f %f", 
					&textures_index[tIndex], &textures_index[tIndex+1]);
				tIndex += 2;
			} else 
			{
				sscanf(buf, "v %f %f %f", 
					&vertices_index[vIndex], &vertices_index[vIndex+1], &vertices_index[vIndex+2]);
				vIndex += 3;
			}
		} else if(buf[0] == 'f') 
		{
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]);

			for(int i = 0; i < 3; i++) {
				v[i]--;
				t[i]--;
				n[i]--;
				/*printf("%d %d %d\n", v[i], t[i], n[i]);
				printf("v: %f %f %f\n", vertices_index[3*v[i]], vertices_index[3*v[i]+1], vertices_index[3*v[i]+2]);
				printf("t: %f %f\n", textures_index[2*t[i]], textures_index[2*t[i]+1]);*/
			}

			for(int i = 0; i < 3; i++) 
			{
				buffer[buf_index] = vertices_index[3*v[i]];
				buffer[buf_index+1] = vertices_index[3*v[i]+1];
				buffer[buf_index+2] = vertices_index[3*v[i]+2] - 1.5; // TRICK
				buffer[buf_index+3] = textures_index[2*t[i]  ];
				buffer[buf_index+4] = textures_index[2*t[i]+1];
				buffer[buf_index+5] = normals_index[3*n[i]   ];
				buffer[buf_index+6] = normals_index[3*n[i] +1]; 
				buffer[buf_index+7] = normals_index[3*n[i] +2];
				buf_index += 8;
			}
		}
	}
 
	int numFaces = buf_index / 24; // 3 * 8		

	fclose(f);
	//delete[] buffer;

	return (new Model(buffer, numFaces));
}

void Model::Render()
{
	
}

float* Model::GetBuffer()
{
	return m_afBuffer;
}