#ifndef __LOADSHADER_H__
#define __LOADSHADER_H__

#include "Log.h"

char * ReadFile(char *fileName);
GLuint loadShader(GLenum shaderType, const char* pSource);
GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

#endif