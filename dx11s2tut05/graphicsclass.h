////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "gamestateclass.h"
#include "modellistclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
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
	bool Frame(GameStateClass*, int);

private:
	bool Render(GameStateClass*);
	void TestIntersection(GameStateClass*);
	bool RayAABBIntersect(bool, GameStateClass*, int, XMFLOAT3 rayOrigin, XMFLOAT3 rayDirection, AabbClass*);

	void RotateCube(GameStateClass*);

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	BitmapClass* m_Bitmap;
	ModelClass* m_Model;
	TextureShaderClass* m_TextureShader;

	// Create the model list object.
	ModelListClass* m_ModelList;

	int m_FrameCounter;
	
	int m_mouseX, m_mouseY;
	int m_oldMouseX, m_oldMouseY;
	float angle;

	XMMATRIX cubeRotation;
	int m_screenWidth, m_screenHeight;
	//CollisionClass* selectionState;

};

#endif