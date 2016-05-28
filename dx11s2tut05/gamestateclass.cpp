#include "gamestateclass.h"


GameStateClass::GameStateClass()
{
	//m_Input = 0;
	//m_Graphics = 0;
}


GameStateClass::GameStateClass(const GameStateClass& other)
{
}


GameStateClass::~GameStateClass()
{
}

bool GameStateClass::Initialize()
{
	m_mouseX, m_mouseY, m_oldMouseX, m_oldMouseY = -1;
	m_cubeRotationMatrix = XMMatrixIdentity();

	return true;
}



//probabilmente inutile
bool GameStateClass::Frame(int mousex, int mousey)
{
	
	return true;


}


void GameStateClass::setCurrentMousePos(int mousex, int mousey){

	m_mouseX = mousex;
	m_mouseY = mousey;
}

void GameStateClass::setOldMousePos(int mousex, int mousey){

	m_oldMouseX = mousex;
	m_oldMouseY = mousey;
}


void GameStateClass::setCubeRotationMatrix(XMMATRIX rotation){

	m_cubeRotationMatrix = rotation;
}

XMMATRIX GameStateClass::getCubeRotationMatrix(){

	return m_cubeRotationMatrix;
}

int GameStateClass::getCurrentMouseX(){
	return m_mouseX;
}
int GameStateClass::getCurrentMouseY(){
	return m_mouseY;
}
int GameStateClass::getOldMouseX(){
	return m_oldMouseX;
}
int GameStateClass::getOldMouseY(){
	return m_oldMouseY;
}

int GameStateClass::getCurrentMinDistance()
{
	return m_tMinDistance;
}

void GameStateClass::setClosestId(int id)
{
	m_ClosestId = id;
}

void GameStateClass::setCurrentMinDistance(double mindistance)
{
	m_tMinDistance = mindistance;

}
