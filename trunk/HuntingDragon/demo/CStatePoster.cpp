#include "CStatePoster.h"

CStatePoster::CStatePoster(): m_iCount(0), CState()
{
}

void CStatePoster::Init()
{
	Log("State Poster: Init");
}

void CStatePoster::Update()
{
	Log("State Poster: Update");
}

void CStatePoster::OnControllerEvent(SControllerEvent Event)
{

}

void CStatePoster::Render()
{
	Log("State Poster: Render");
}

void CStatePoster::Exit()
{
	Log("State Poster: Exit");
}
