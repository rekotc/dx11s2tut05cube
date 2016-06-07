////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <string>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "gamestateclass.h"
#include "modellistclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "consoleclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(GameStateClass*, int, float, ConsoleClass*);

private:
	bool Render(GameStateClass*, ConsoleClass*);
	void TestIntersection(GameStateClass*);
	bool RayAABBIntersect(bool, GameStateClass*, int, XMVECTOR , XMVECTOR, AabbClass*);
	void UpdateCubeColors(GameStateClass*);
	void RotateCube(GameStateClass*, int, float, ConsoleClass*);

	static void CompleteRotation(GameStateClass*, ModelListClass*, ConsoleClass*);
	static float calculateDelta(float, float);

	static void resetSelection(GameStateClass*, ModelListClass*);

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	BitmapClass* m_Bitmap;
	ModelClass* m_Model;

	BitmapClass* m_Background;
	BitmapClass* m_ConsoleGUI;
	TextClass* m_Text;

	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	// Create the model list object.
	ModelListClass* m_ModelList;

	int m_FrameCounter;
	
	int m_mouseX, m_mouseY;
	int m_oldMouseX, m_oldMouseY;
	

	XMMATRIX cubeRotation;
	int m_screenWidth, m_screenHeight;
	//CollisionClass* selectionState;

};

#endif