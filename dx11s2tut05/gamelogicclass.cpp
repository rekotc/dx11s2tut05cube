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
bool GameLogicClass::HandleInput(GameStateClass* gamestate, InputClass* input)
{
	bool result, onClick;
	int mouseX, mouseY;

	gamestate->setCurrentMousePos(input->getCursorPosX(), input->getCursorPosY());


	short test = input->getMouseLButtonT();
	if (test == 1){

		int ciao = 98;
	}
	//salvo lo stato del left mouse button
	gamestate->setLeftMouseButtonClick(input->getMouseLButton());

	//se il mouse non è premuto in questo istante e NON lo era nemmeno prima allora:
	//setto a false il wasclicked, il dragged e il released.
	if (gamestate->isLeftMouseButtonClicked() == false && gamestate->LeftMouseButtonWasClicked() == false){
			gamestate->setLeftMouseButtonWasClicked(false);
			gamestate->setLeftMouseButtonIsDragged(false);
			gamestate->setLeftMouseButtonWasReleased(true);

		}
	else
	//se il mouse non è premuto in questo istante ma LO ERA l'istante precedente, significa che è stato rilasciato
	//setto a falso il wasclicked e il dragged, setto a true il released.
	if (gamestate->isLeftMouseButtonClicked() == false && gamestate->LeftMouseButtonWasClicked() == true){
			gamestate->setLeftMouseButtonWasClicked(false);
			gamestate->setLeftMouseButtonIsDragged(false);
			gamestate->setLeftMouseButtonWasReleased(true);

		}
	//se il mouse è premuto in questo istante e prima NON lo era, significa che è il primo click, allora:
	//setto a true il wasclicked (vale dall'istante successivo), setto a false il dragged e il released.
	else
		if (gamestate->isLeftMouseButtonClicked() == true && gamestate->LeftMouseButtonWasClicked() == false){
			gamestate->setLeftMouseButtonWasClicked(true);
			gamestate->setLeftMouseButtonIsDragged(false);
			gamestate->setLeftMouseButtonWasReleased(false);
		}
	else
	//se il mouse è premuto e lo era anche prima, vuol dire che sto trascinando, allora:
	//setto a true il dragged, setto a false il released
	if (gamestate->isLeftMouseButtonClicked() == true && gamestate->LeftMouseButtonWasClicked() == true){
		gamestate->setLeftMouseButtonIsDragged(true);
		gamestate->setLeftMouseButtonWasReleased(false);
	}


	return true;
}