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
	m_tMinDistance = 999999999;
	m_mouseX, m_mouseY, m_oldMouseX, m_oldMouseY = -1;
	m_SelectedId = -1;

	leftMouseButtonIsClicked = false;
	m_MouseHoverID = -1;
	m_cubeRotationMatrix = XMMatrixIdentity();

	leftMouseButtonWasClicked	= false;
	leftMouseButtonIsDragged	= false;

	leftMouseButtonWasReleased = false;

	lock = false;

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



void GameStateClass::setCurrentMinDistance(double mindistance)
{
	m_tMinDistance = mindistance;

}

void GameStateClass::resetCurrentMinDistance()
{
	m_tMinDistance = 999999999;;

}

void GameStateClass::setMouseHoverID(int id)
{
	m_MouseHoverID = id;
}

int GameStateClass::getMouseHoverID()
{
	return m_MouseHoverID;
}

void GameStateClass::resetMouseHoverID(){
	m_MouseHoverID = -1;
}

bool GameStateClass::isLeftMouseButtonClicked(){

	return leftMouseButtonIsClicked;
}

void GameStateClass::setLeftMouseButtonClick(bool b){

	leftMouseButtonIsClicked = b;
}

bool GameStateClass::LeftMouseButtonWasClicked(){

	return leftMouseButtonWasClicked;
}

void GameStateClass::setLeftMouseButtonWasClicked(bool b){

	leftMouseButtonWasClicked = b;
}

bool GameStateClass::LeftMouseButtonIsDragged(){

	return leftMouseButtonIsDragged;
}

void GameStateClass::setLeftMouseButtonIsDragged(bool b){

	leftMouseButtonIsDragged = b;
}

bool GameStateClass::LeftMouseButtonWasReleased(){

	return leftMouseButtonWasReleased;
}

void GameStateClass::setLeftMouseButtonWasReleased(bool b){

	leftMouseButtonWasReleased = b;
}

void GameStateClass::setLock(bool b){

	lock = b;
}

bool GameStateClass::getLock(){

	return lock;
}