#include "CCharacter.h"

CCharacter::CCharacter()	
{
	Init();
}

CCharacter::~CCharacter()
{

}

void CCharacter::Init()
{
	m_Velocity = 1;

	m_vecDir = Vector3(1, 0, 0);
	m_vecNormal = Vector3(0, 0, 1);
	m_Acceleration = Vector3(0, 0, 0);
	m_Position = Vector3(0, 0, 0);
	m_CurAction = ACTION_RUN;
	m_iCurFrames = 0;
	xangle = 0;

	m_matWorld.LoadIdentity();
}

void CCharacter::Update()
{
	// normalize all vectors
	m_vecDir = m_vecDir.normalize();
	m_vecNormal = m_vecNormal.normalize();

	// update character's current frame
	m_iCurFrames++;
	if(m_iCurFrames < m_Frames[m_CurAction][START_FRAME] || m_iCurFrames > m_Frames[m_CurAction][END_FRAME])
	{
		m_iCurFrames = m_Frames[m_CurAction][START_FRAME];
	}

	// update position
	float dt = 0.1f;
	m_Position = m_Position + dt * m_Velocity * m_vecDir;


	

	//// fix camera
	//m_Camera.Perspective(45, 4.0f/3.0f, 1.0f, 100.0f);
	//m_Camera.Lookat(
	//	0, 0, 5.0f,
	//	0, 0, 0,
	//	1.0f, 0, 0);
	//m_Camera.BuildViewMatrix();	

	// update z-rotation angle
	xangle = -atan(m_vecDir[1] / m_vecDir[0]) * RAD_2_DEG;
	if(m_vecDir[0] < 0) xangle += 180.0f;

	// update world matrix
	m_matWorld.LoadIdentity();
	m_matWorld.Translate(m_Position[0], m_Position[1], m_Position[2]);
	m_matWorld.Rotate(xangle, Z_AXIS);
}

void CCharacter::LoadActions(const char* strCfgName)
{
	FILE* f;
	char buf[100];
	char action[20];
	int startFrame, endFrame;

	f = fopen(strCfgName, "r");
	
	while(!feof(f))
	{
		//get action
		fgets(buf, 100, f);
		sscanf(buf, "%s %d %d", action, &startFrame, &endFrame);
		

		// load frames of action
		if(strcmp(action, "STAND") == 0)
		{
			m_Frames[ACTION_STAND][START_FRAME] = startFrame;
			m_Frames[ACTION_STAND][END_FRAME] = endFrame;
		}

		if(strcmp(action, "RUN") == 0)
		{
			m_Frames[ACTION_RUN][START_FRAME] = startFrame;
			m_Frames[ACTION_RUN][END_FRAME] = endFrame;
		}

		if(strcmp(action, "ATTACK") == 0)
		{
			m_Frames[ACTION_ATTACK][START_FRAME] = startFrame;
			m_Frames[ACTION_ATTACK][END_FRAME] = endFrame;
		}

		if(strcmp(action, "DIE") == 0)
		{
			m_Frames[ACTION_DIE][START_FRAME] = startFrame;
			m_Frames[ACTION_DIE][END_FRAME] = endFrame;
		}
	}

	fclose(f);
}

void CCharacter::Render(Matrix* vpMatrix)
{
	Matrix mvpMatrix = *vpMatrix * m_matWorld;

	CGraphics3D::GetInstance()->SetMVPMatrix(mvpMatrix.GetData());

	CModel::Render(m_iCurFrames);
	Sleep(50);
}

void CCharacter::Release()
{
}