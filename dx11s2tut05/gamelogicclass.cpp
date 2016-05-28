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

bool GameLogicClass::Frame(GameStateClass* GameState)
{

	//XMMATRIX cubeRotation = GameState->getCubeRotationMatrix();
	
	HandleInput(GameState);

	return true;
}

//questa funzione deve verificare lo stato del mouse e settare i relativi parametri in GameState
//in modo tale che poi, nella classe graphicsclass, sia possibile eseguire tutte le operazioni di picking/intersection/ecc
bool GameLogicClass::HandleInput(GameStateClass* GameState)
{
	bool result, onClick;
	int mouseX, mouseY;


	//salvo lo stato del left mouse button
	m_leftButtonIsClicked = m_Input->IsLeftMouseButtonDown();

	//se è stato premuto
	if (m_leftButtonIsClicked == true){
		//e all'iterazione precedente il mouse era premuto
		if (m_leftButtonWasClicked == true){
			//significa che sto trascinando un oggetto
			m_leftButtonIsBeingDragged = true;
		}
		else{
			m_leftButtonWasClicked = true;
		}

	}
	//altrimenti vuol dire che non ho cliccato, quindi il mouse eventualmente è stato rilasciato, o è rimasto non premuto.
	else if (m_leftButtonIsClicked == false) {
		m_leftButtonWasClicked = false;
		m_leftButtonIsBeingDragged = false;

		//devo completare la rotazione del cubo se questo flag è settato
		if (m_cubeIsBeingRotated == true){

			result = completeRotation(3, m_axis);
		}


	}

	m_Input->GetMouseLocation(m_mouseX, m_mouseY);

	//se non ho cliccato o se non stavo trascinando devo comunque aggiornare l'interfaccia
	//se invece il pulsante del mouse fosse cliccato e stessi trascinando, non dovrei aggiornare nulla.

	if (m_leftButtonIsClicked == false || m_leftButtonIsBeingDragged == false){

		//resetto la selezione corrente
		resetSelection(selectionState->getClosestId());
		m_Text->SetIntersection(false, selectionState->getClosestId(), m_D3D->GetDeviceContext());
		//resetto le coordinate del mouse necessarie per calcolare lo spostamento dell'oggetto selezionato.
		m_Input->setOldMouseX(-1);
		m_Input->setOldMouseY(-1);
		//Eseguo il test per l'intersezione
		TestIntersection();
		//se ho trovato una qualche intersezione
		if (selectionState->getClosestId() != -1){
			result = handleIntersection();
		}


	}
	//altrimenti vuol dire che sto trascinando l'oggetto, devo spostarlo di conseguenza.
	else if (m_leftButtonIsClicked == true && m_leftButtonIsBeingDragged == true && selectionState->getClosestId() != -1) {

		moveObject();
	}

	return true;
}