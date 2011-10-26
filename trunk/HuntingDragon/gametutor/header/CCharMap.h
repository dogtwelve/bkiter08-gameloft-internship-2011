#ifndef __CCHARMAP_H__
#define __CCHARMAP_H__

#include <queue>
using namespace std;

typedef struct SCM
{
	SCM(char _id, int _x, int _y, int _w, int _h)
		:id(_id), x(_x), y(_y), w(_w), h(_h) {}

	char id;
	int x, y, w, h;
} SCharMap;

class CCharMap
{
public:
	CCharMap();
	virtual ~CCharMap();
public:
	void AddMap(char id, int x, int y, int w, int h);
	void AddMapFromFile(char* filename);
	SCharMap* GetMap(char id); // return NULL if charmap is not exist
private:
	vector<SCharMap*> m_Map;
};

#endif