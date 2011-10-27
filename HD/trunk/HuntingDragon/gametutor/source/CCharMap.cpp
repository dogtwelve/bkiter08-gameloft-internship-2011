#include "CCharMap.h"

CCharMap::CCharMap()
{
	
}

CCharMap::~CCharMap()
{
	for(int i = 0; i < m_Map.size(); i++) 
	{
		m_Map[i];
	}
}

void CCharMap::AddMap(char id, int x, int y, int w, int h)
{
	m_Map.push_back(new SCharMap(id, x, y, w, h));
}

SCharMap* CCharMap::GetMap(char id)
{
	for(int i = 0; i < m_Map.size(); i++)
	{
		if(id == m_Map[i]->id) 
		{
			return m_Map[i];
		}
	}
	return NULL;
}

void CCharMap::AddMapFromFile(char* filename)
{
	FILE* f;
	f = fopen(filename, "r");

	char buf[100];
	char id;
	int x, y, w, h;

	while(!feof(f))
	{
		fgets(buf, 100, f);
		sscanf(buf, "%c %d %d %d %d", &id, &x, &y, &w, &h);
		AddMap(id, x, y, w, h);
	}

	fclose(f);
}