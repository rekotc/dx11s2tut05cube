#include "gamelogicclass.h"


GameLogicClass::GameLogicClass()
{
	//m_Input = 0;
	//m_Graphics = 0;
}


GameLogicClass::GameLogicClass(const GameLogicClass& other)
{
}


GameLogicClass::~GameLogicClass()
{
}

bool GameLogicClass::Frame(GameStateClass* GameState, InputClass* input)
{

	//XMMATRIX cubeRotation = GameState->getCubeRotationMatrix();
	
	HandleInput(GameState, input);

	return true;
}

//questa funzione deve verificare lo stato del mouse e settare i relativi parametri in GameState
//in modo tale che poi, nella classe graphicsclass, sia possibile eseguire tutte le operazioni di picking/intersection/ecc
bool GameLogicClass::HandleInput(GameStateClass* GameState, InputClass* input)
{
	bool result, onClick;
	int mouseX, mouseY;


	//salvo lo stato del left mouse button
	bool m_leftButtonIsClicked = input->getMouseLButton();
		

	return true;
}