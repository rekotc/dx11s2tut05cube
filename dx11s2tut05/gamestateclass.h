////////////////////////////////////////////////////////////////////////////////
// Filename: gamestateclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMESTATECLASS_H_
#define _GAMESTATECLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////



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
class GameStateClass
{
public:
	GameStateClass();
	GameStateClass(const GameStateClass&);
	~GameStateClass();

	bool Initialize();
	void Shutdown();
	bool Frame(int, int);
	void setCurrentMousePos(int, int);

	int getCurrentMouseX();
	int getCurrentMouseY();
	int getOldMouseX();
	int getOldMouseY();

	void setOldMousePos(int, int);
	void setCubeRotationMatrix(XMMATRIX);
	XMMATRIX getCubeRotationMatrix();

	
	int getCurrentSelectedId();
	int getCurrentHoverId();
	int getCurrentMinDistance();
	int getLastSelectedId();
	int getLastHoverId();

	
	void setCurrentSelectedId(int);

	void setCurrentHoverId(int);
	
	void setLastSelectedId(int);
	void setLastHoverId(int);
	void setClicked(bool);
	bool getClicked();

	//NUOVE
	void setCurrentMinDistance(double);
	void resetCurrentMinDistance();

	int getMouseHoverID();
	void setMouseHoverID(int);
	void resetMouseHoverID();

	void setPreviousMouseHoverID(int);
	int getPreviousMouseHoverID();

	bool isLeftMouseButtonClicked();
	void setLeftMouseButtonClick(bool);

	bool LeftMouseButtonWasClicked();
	void setLeftMouseButtonWasClicked(bool);

	bool LeftMouseButtonIsDragged();
	void setLeftMouseButtonIsDragged(bool);

	bool LeftMouseButtonWasReleased();
	void setLeftMouseButtonWasReleased(bool);

	void setLock(bool);
	bool getLock();

	void setConsoleEnabled(bool);
	bool getConsoleEnabled();

	void setCubeIsBeingRotated(bool);
	bool getCubeIsBeingRotated();

	void setLockAroundXAxis(bool);
	bool getLockAroundXAxis();

	void setLockAroundYAxis(bool);
	bool getLockAroundYAxis();

	void setTimeSinceLock(float);
	float getTimeSinceLock();

	void setTimerIsActive(bool);
	bool getTimerIsActive();

	void addSumDeltaX(int);
	int getSumDeltaX();

	void addSumDeltaY(int);
	int getSumDeltaY();

	void resetSumDeltaX();
	void resetSumDeltaY();
	
private:
	//bool Render();

private:
	int m_mouseX, m_mouseY;
	int m_oldMouseX, m_oldMouseY;
	float angle;
	XMMATRIX m_cubeRotationMatrix;

	//controllare cosa serve
	int m_SelectedId, m_LastSelectedId, m_HoverId, m_LastHoverId;

	bool lockAroundXAxis;
	bool lockAroundYAxis;
	float timeSinceLock;
	int sumDeltaX, sumDeltaY;

	int m_MouseHoverID;
	int m_PreviousMouseHoverID;
	bool m_CubeIsBeingRotated;
	bool leftMouseButtonIsClicked;
	bool leftMouseButtonWasClicked;
	bool leftMouseButtonIsDragged;
	bool leftMouseButtonWasReleased;
	double m_tMinDistance;


	bool timerIsActive;

	bool consoleEnabled;

	//test
	bool lock;

};

#endif