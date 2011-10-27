#ifndef __CGLPIPELINEDRIVER_H__
#define __CGLPIPELINEDRIVER_H__

#include "Header.h"
#include "CSingleton.h"
#include "SGraphics.h"
#include "LoadShader.h"

#define EGLPD_DEFAUL_MAX_INDICES 100000

namespace GameTutor
{

	enum EGLPipelineDriverPrimaryType
	{
		EGLPD_PRIYTPE_FLOAT = GL_FLOAT,
		EGLPD_PRIYTPE_UINT = GL_UNSIGNED_INT,
	};

	enum EGLPipelineDriverRenderMode
	{
		EGLPD_RENDERMODE_TRIANGLE = GL_TRIANGLES,
		EGLPD_RENDERMODE_TRIANGLESTRIP = GL_TRIANGLE_STRIP,
	};

	enum EGLPipelineDriverAttribType
	{
		EGLPD_ATTRIB_VERTEX,
		EGLPD_ATTRIB_NORMAL,
		EGLPD_ATTRIB_COLOR,
		EGLPD_ATTRIB_TEXCOOR,
	};

	enum EGLPipelineDriverMatrixMode
	{
		EGLPD_MATRIXMODE_PROJECTION,
		EGLPD_ATTRIB_MODELVIEW,
	};

	enum EGLPipelineDriverPixelFormat
	{
		EGLPD_PIXFMT_R8G8B8 = GL_RGB,
		EGLPD_PIXFMT_R8G8B8A8 = GL_RGBA,
	};

	class CGLPipelineDriver:public CSingleton<CGLPipelineDriver>
	{
		friend class CSingleton<CGLPipelineDriver>;
	protected:
		CGLPipelineDriver():
			m_isUseAlpha(false), m_isUse2DTexture(false)
		{
			glDisable(GL_BLEND | GL_TEXTURE_2D);
			//glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			for (int i = 0; i < EGLPD_ATTRIB_TEXCOOR - EGLPD_ATTRIB_VERTEX + 1; i++)
			{
				m_isUseAttribPointer[i] = false;
			}			

			for (int i = 0; i < EGLPD_DEFAUL_MAX_INDICES; i++)
			{
				m_iAutoIndices[i] = i;
			}
			
			char* strColorVertexShader = ReadFile("../resources/shader/vColorShader.glsl");
			char* strColorFragShader = ReadFile("../resources/shader/fColorShader.glsl");

			uShaderProgram = createProgram(strColorVertexShader, strColorFragShader);

			uVertexHandle = glGetAttribLocation(uShaderProgram, "a_vertices");
			uColorHandle = glGetAttribLocation(uShaderProgram, "a_colors");
			uTexHandle = glGetAttribLocation(uShaderProgram, "a_uv");
			uMVPMatHandle = glGetUniformLocation(uShaderProgram, "u_mvpMatrix");
		}
	public:
		//-----------------------------------------------
		// Set Color
		//-----------------------------------------------
		template <class T>
		void SetColor(T alpha, T red, T green, T blue)
		{
			if (sizeof(T) == 1)
			{
				SetColor<__UINT8>(__UINT8(alpha), __UINT8(red), __UINT8(green), __UINT8(blue));
			}
			else
			{
				BREAK("Invalid type");
			}
		}
		template <>
		void SetColor<float>(float alpha, float red, float green, float blue)
		{
			//glColor4f(red, green, blue, alpha);
		}
		template <>
		void SetColor<__UINT8>(__UINT8 alpha, __UINT8 red, __UINT8 green, __UINT8 blue)
		{
			//glColor4f(red/255.0f, green/255.0f, blue/255.0f, alpha/255.0f);
		}

		//-----------------------------------------------
		// Set Blending
		//-----------------------------------------------
		void EnableBlending(bool val)
		{
			if (val != m_isUseAlpha)
			{
				m_isUseAlpha = val;
				if (m_isUseAlpha)
				{
					glEnable (GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				else
				{
					glDisable(GL_BLEND);
				}
			}
			
		}
		
		//-----------------------------------------------
		// Attribute Pointer
		//-----------------------------------------------
		void AttributePointer(enum EGLPipelineDriverAttribType attribType, int size, enum EGLPipelineDriverPrimaryType primType, __UINT32 stride, void* pointer)
		{
			float *xx = (float*)pointer;
			switch (attribType)
			{
			case EGLPD_ATTRIB_VERTEX:
				glVertexAttribPointer(uVertexHandle, size, __INT32(primType), GL_FALSE, stride, pointer);
				break;
			case EGLPD_ATTRIB_NORMAL:
				//[TODO]: implement normal attribute pointer
				break;
			case EGLPD_ATTRIB_COLOR:
				glVertexAttribPointer(uColorHandle, size, __INT32(primType), GL_FALSE, stride, pointer);
				break;
			case EGLPD_ATTRIB_TEXCOOR:
				glVertexAttribPointer(uTexHandle, size, __INT32(primType), GL_FALSE, stride, pointer);
				break;
			}

		}

		void UniformMatrix(float* matrix)
		{
			glUniformMatrix4fv(uMVPMatHandle, 1, GL_FALSE, matrix);
		}

		//-----------------------------------------------
		// Enable client state (enable/disable attrib pointer)
		//-----------------------------------------------
		void EnableAttribPointer(enum EGLPipelineDriverAttribType attribType, bool isUse)
		{
			if (isUse)
			{
				if (!m_isUseAttribPointer[attribType])
				{
					m_isUseAttribPointer[attribType] = true;

					switch(attribType)
					{
					case EGLPD_ATTRIB_VERTEX:
						glEnableVertexAttribArray(uVertexHandle);
						break;
					case EGLPD_ATTRIB_COLOR:
						glEnableVertexAttribArray(uColorHandle);
						break;
					case EGLPD_ATTRIB_TEXCOOR:
						glEnableVertexAttribArray(uTexHandle);
						break;
					}
				}
			}
			else
			{
				if (m_isUseAttribPointer[attribType])
				{
					m_isUseAttribPointer[attribType] = false;
					
					switch(attribType)
					{
					case EGLPD_ATTRIB_VERTEX:
						glDisableVertexAttribArray(uVertexHandle);
						break;
					case EGLPD_ATTRIB_COLOR:
						glDisableVertexAttribArray(uColorHandle);
						break;
					case EGLPD_ATTRIB_TEXCOOR:
						glDisableVertexAttribArray(uTexHandle);
						break;
					}
				}
			}
			
		}

		//-----------------------------------------------
		// Draw Array
		//-----------------------------------------------
		void DrawElements(enum EGLPipelineDriverRenderMode mode, __UINT32 numOfIndices, enum EGLPipelineDriverPrimaryType primType, void *indices)
		{
			glUseProgram(uShaderProgram);
			
			if (!indices)
			{
				indices = m_iAutoIndices;
				primType = EGLPD_PRIYTPE_UINT;
			}
			BREAK_IF(numOfIndices > EGLPD_DEFAUL_MAX_INDICES, "numOfIndices is bigger than EGLPD_DEFAUL_MAX_INDICES");
			glDrawElements(mode, numOfIndices, primType, indices);
		}
		void DrawElements(enum EGLPipelineDriverRenderMode mode, __UINT32 numOfIndices)
		{
			DrawElements(mode, numOfIndices, EGLPD_PRIYTPE_UINT, 0);
		};
		//-----------------------------------------------
		// Clear Screen
		//-----------------------------------------------
		void Clear(SColor<float> c)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(c.Red, c.Green, c.Blue, c.Alpha);
		}

		//-----------------------------------------------
		// Set view port
		//-----------------------------------------------
		void Viewport(SRect<__INT32> rect)
		{
			glViewport(rect.X, rect.Y, rect.W, rect.H);
		}

		//-----------------------------------------------
		// Othor
		//-----------------------------------------------
		void Ortho(float left, float right, float top, float bottom, float znear, float zfar)
		{
			//glOrtho(left, right, bottom, top, znear, zfar);
		}
	
		
		void LoadIdentity(enum EGLPipelineDriverMatrixMode mode)
		{
			/*EnableMatrixMode(mode);
			glLoadIdentity();*/
		}

	//-----------------------------------------------
		// Texture
		//-----------------------------------------------
		void EnableTexture2D(bool val)
		{
			if (val != m_isUse2DTexture)
			{
				m_isUse2DTexture = val;
				if (m_isUse2DTexture)
				{
					glEnable (GL_TEXTURE_2D);
				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}
			}
		}

		__UINT32 AddTexure2D(int level, EGLPipelineDriverPixelFormat format, int width, int height, int border, __UINT8 *pixel)
		{
			EnableTexture2D(true);
			__UINT32 texname = 0;
			glGenTextures(1, &texname);
			glBindTexture(GL_TEXTURE_2D, texname);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_LINEAR
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_LINEAR
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, level, format, width, height, border, format, GL_UNSIGNED_BYTE, pixel);
			return texname;
		}


		void BindTexture2D(__UINT32 texname)
		{
			glBindTexture(GL_TEXTURE_2D, texname);
		}

		void FreeTexture2D(__UINT32 texname)
		{
			glDeleteTextures(1, &texname );
		}

	private:
		bool m_isUseAttribPointer[EGLPD_ATTRIB_TEXCOOR - EGLPD_ATTRIB_VERTEX + 1];
		__UINT32 m_iAttribMapping[EGLPD_ATTRIB_TEXCOOR - EGLPD_ATTRIB_VERTEX + 1];
		__UINT32 m_iAutoIndices[EGLPD_DEFAUL_MAX_INDICES];
		bool m_isUseAlpha;
		bool m_isUse2DTexture;

		// shader programs
		GLuint uShaderProgram;
		GLuint uVertexHandle;
		GLuint uColorHandle;
		GLuint uTexHandle;
		GLuint uMVPMatHandle;
	};
}

#endif