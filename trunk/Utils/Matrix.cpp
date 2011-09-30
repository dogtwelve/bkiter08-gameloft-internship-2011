#include "Matrix.h"


Matrix::Matrix(void)
{
	LoadIdentity();
}


Matrix::~Matrix(void)
{
}

Matrix::Matrix(float m[4][4])
{
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			this->m[i][j] = m[i][j];
		}
	}
}

void Matrix::LoadIdentity()
{
	m[0][0] = 1;
	m[1][0] = 0;
	m[2][0] = 0;
	m[3][0] = 0;

	m[0][1] = 0;
	m[1][1] = 1;
	m[2][1] = 0;
	m[3][1] = 0;

	m[0][2] = 0;
	m[1][2] = 0;
	m[2][2] = 1;
	m[3][2] = 0;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;
}

float* Matrix::ToArray()
{
	return (float*) m;
}

void Matrix::MakeTranspose()
{
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < i; j++) {
			// swap m[i][j], m[j][i]		
			float temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
		}
	}
}

Matrix Matrix::PerspectiveFov(float fovy, float aspect, float znear, float zfar)
{
	float m[4][4];
	float f = 1/tan(fovy * DEG_2_RAD);

	m[0][0]  = f/aspect;
	m[1][0]  = 0;
	m[2][0]  = 0;
	m[3][0]  = 0;

	m[0][1]  = 0;
	m[1][1]  = f;
	m[2][1]  = 0;
	m[3][1]  = 0;

	m[0][2]  = 0;
	m[1][2]  = 0;
	m[2][2] = (zfar+znear)/(znear-zfar);
	m[3][2] = -1;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 2*znear*zfar/(znear-zfar);
	m[3][3] = 0;

	return Matrix(m);
}

Matrix Matrix::Perspective(float left, float right, float bottom, float top, float near, float far)
{
	float m[4][4];
	
	m[0][0]  = 2.0f*near/(right-left);
	m[1][0]  = 0;
	m[2][0]  = 0;
	m[3][0]  = 0;

	m[0][1]  = 0;
	m[1][1]  = 2.0f*near/(top-bottom);
	m[2][1]  = 0;
	m[3][1]  = 0;

	m[0][2]  = (right+left)/(right-left);
	m[1][2]  = (top+bottom)/(top-bottom);
	m[2][2] = -(far+near)/(far-near);
	m[3][2] = -1.0f;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = -2.0f*far*near/(far-near);
	m[3][3] = 0;

	return Matrix(m);
}

Matrix Matrix::Ortho(float left, float right, float bottom, float top, float near, float far)
{
	float m[4][4];

	m[0][0]  = 2/(right-left);
	m[1][0]  = 0;
	m[2][0]  = 0;
	m[3][0]  = 0;

	m[0][1]  = 0;
	m[1][1]  = 2/(top-bottom);
	m[2][1]  = 0;
	m[3][1]  = 0;

	m[0][2]  = 0;
	m[1][2]  = 0;
	m[2][2] = -2/(far-near);
	m[3][2] = -1;

	m[0][3] = -(right+left)/(right-left);
	m[1][3] = -(top+bottom)/(top-bottom);
	m[2][3] = -(far+near)/(far-near);
	m[3][3] = 1;

	return Matrix(m);
}

Matrix Matrix::RotationX(float angle)
{
	float m[4][4];

	m[0][0]  = 1;
	m[1][0]  = 0;
	m[2][0]  = 0;
	m[3][0]  = 0;

	m[0][1]  = 0;
	m[1][1]  = cos(angle * DEG_2_RAD);
	m[2][1]  = sin(angle * DEG_2_RAD);
	m[3][1]  = 0;

	m[0][2]  = 0;
	m[1][2]  = -sin(angle * DEG_2_RAD);
	m[2][2] = cos(angle * DEG_2_RAD);
	m[3][2] = 0;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;

	return Matrix(m);
}

Matrix Matrix::RotationY(float angle)
{
	float m[4][4];

	m[0][0]  = cos(angle * DEG_2_RAD);
	m[1][0]  = 0;
	m[2][0]  = -sin(angle * DEG_2_RAD);
	m[3][0]  = 0;

	m[0][1]  = 0;
	m[1][1]  = 1;
	m[2][1]  = 0;
	m[3][1]  = 0;

	m[0][2]  = sin(angle * DEG_2_RAD);
	m[1][2]  = 0;
	m[2][2] = cos(angle * DEG_2_RAD);
	m[3][2] = 0;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;

	return Matrix(m);
}

Matrix Matrix::LookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	return LookAt(eye.getX(), eye.getY(), eye.getZ(),
		center.getX(), center.getY(), center.getZ(),
		up.getX(), up.getY(), up.getZ());
}


Matrix Matrix::LookAt(float eyex, float eyey, float eyez,
	float centerx, float centery, float centerz,
	float upx, float upy, float upz) 
{
	float m[4][4];
	//TODO: need to implement
	return Matrix(m);
}

Matrix Matrix::Multiply(Matrix & a, Matrix & b)
{
	float* ma = a.ToArray();
	float* mb = b.ToArray();

	float m[4][4];
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			m[r][c] = 0;
		}
	}

	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			for(int i = 0; i < 4; i++) {
				m[r][c] += ma[4*r+i] * mb[4*i+c];
			}
		}
	}

	return Matrix(m);
}