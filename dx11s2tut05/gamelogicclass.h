////////////////////////////////////////////////////////////////////////////////
// Filename: gamelogicclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMELOGICCLASS_H_
#define _GAMELOGICCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "gamestateclass.h"
#include "inputclass.h"

/////////////
// GLOBALS //
/////////////
#include "C:\Program Files (x86)\Windows Kits\8.1\Include\um\d3d11.h"
//import esplicito altrimenti va a prendersi quella dell'SDK vecchio
#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: GameStateClass
////////////////////////////////////////////////////////////////////////////////
class GameLogicClass
{
public:
	GameLogicClass();
	GameLogicClass(const GameLogicClass&);
	~GameLogicClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(GameStateClass*, InputClass*);

	//bool Render();
	

private:
	
	bool HandleInput(GameStateClass*, InputClass*);

private:
	int m_mouseX, m_mouseY;
	int m_oldMouseX, m_oldMouseY;
	float angle;
	
	

};

#endif