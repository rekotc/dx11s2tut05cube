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
	m_mouseX = -1;
	m_mouseY = -1;
	m_oldMouseX = -1;
	m_oldMouseY = -1;

	m_SelectedId = -1;

	leftMouseButtonIsClicked = false;
	m_MouseHoverID = -1;
	m_PreviousMouseHoverID = -1;
	m_cubeRotationMatrix = XMMatrixIdentity();

	leftMouseButtonWasClicked	= false;
	leftMouseButtonIsDragged	= false;

	leftMouseButtonWasReleased = false;

	m_CubeIsBeingRotated = false;

	lock = false;
	consoleEnabled = false;

	lockAroundXAxis = false;
	lockAroundYAxis = false;
	sumDeltaX = 0;
	sumDeltaY = 0;

	timeSinceLock = 0.0f;
	timerIsActive = false;

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

void GameStateClass::setConsoleEnabled(bool c){

	consoleEnabled = c;
}
bool GameStateClass::getConsoleEnabled(){

	return consoleEnabled;
}

void GameStateClass::setPreviousMouseHoverID(int p){

	m_PreviousMouseHoverID = p;
}
int GameStateClass::getPreviousMouseHoverID(){

	return m_PreviousMouseHoverID;
}

void GameStateClass::setCubeIsBeingRotated(bool c){

	m_CubeIsBeingRotated = c;
}

bool GameStateClass::getCubeIsBeingRotated(){

	return m_CubeIsBeingRotated;
}


void  GameStateClass::setLockAroundXAxis(bool l){

	lockAroundXAxis = l;
}

bool  GameStateClass::getLockAroundXAxis(){

	return lockAroundXAxis;
}

void  GameStateClass::setLockAroundYAxis(bool l){

	lockAroundYAxis = l;
}
bool  GameStateClass::getLockAroundYAxis(){

	return lockAroundYAxis;
}

void GameStateClass::setTimeSinceLock(float e){

	timeSinceLock = e;
}
float GameStateClass::getTimeSinceLock(){

	return timeSinceLock;
}

void GameStateClass::setTimerIsActive(bool b){

	timerIsActive = b;
}
bool GameStateClass::getTimerIsActive(){

	return timerIsActive;
}

void GameStateClass::addSumDeltaX(int i){

	sumDeltaX = sumDeltaX + i;

}
int GameStateClass::getSumDeltaX(){

	return sumDeltaX;
}

void GameStateClass::addSumDeltaY(int i){

	sumDeltaY = sumDeltaY + i;
}
int GameStateClass::getSumDeltaY(){

	return sumDeltaY;

}

void GameStateClass::resetSumDeltaX(){
	sumDeltaX = 0.0f;
}
void GameStateClass::resetSumDeltaY(){
	sumDeltaY = 0.0f;
}