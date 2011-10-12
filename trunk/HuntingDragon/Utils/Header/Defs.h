#ifndef __DEFS_H__
#define __DEFS_H__

typedef struct
{
   // Handle to a program object
   GLuint programObject;
   GLuint iVerticesLoc;
   GLuint iColorLoc;
   GLuint iVerticesLoc1;
   GLuint iColorLoc1;
   GLuint iMVPMatrix;
   GLuint iUV;
   GLuint u_texture;
} UserData;

#endif