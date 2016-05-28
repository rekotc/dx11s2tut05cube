////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;
	m_ModelList = 0;


}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	m_screenWidth	= screenWidth;
	m_screenHeight = screenHeight;

	cubeRotation = XMMatrixIdentity();

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(10.0f, 10.0f, -5.0f);

	// Create the model list object.
	m_ModelList = new ModelListClass;
	if (!m_ModelList)
	{
		return false;
	}

	// Initialize the model list object.
	result = m_ModelList->Initialize(9);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}

	m_ModelList->SetData(0, 10.0f, 10.0f, 10.0f);
	m_ModelList->SetData(1,12.0f, 10.0f, 10.0f);
	m_ModelList->SetData(2,14.0f, 10.0f, 10.0f);
	m_ModelList->SetData(3,10.0f, 12.0f, 10.0f);
	m_ModelList->SetData(4,12.0f, 12.0f, 10.0f);
	m_ModelList->SetData(5,14.0f, 12.0f, 10.0f);
	m_ModelList->SetData(6,10.0f, 14.0f, 10.0f);
	m_ModelList->SetData(7,12.0f, 14.0f, 10.0f);
	m_ModelList->SetData(8,14.0f, 14.0f, 10.0f);

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../data/dice.txt", "../data/dice.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, "../data/mouse.tga", 32, 32);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}




	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the model object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(GameStateClass* gamestate, int framecounter)
{
	bool result;
	m_FrameCounter = framecounter;
	//l'intersezione va verificata sempre, sia se ho premuto un pulsante del mouse sia se sto semplicemente muovendo il cursore
	TestIntersection(gamestate);
	//aggiorno il colore del cubo in base all'eventuale intersezione trovata.
	UpdateCubeColors(gamestate);
	// Render the graphics scene.
	result = Render(gamestate);
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(GameStateClass* gamestate )
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	XMMATRIX translateMatrix, rotateMatrix;
	bool result;
	int index;
	XMFLOAT3 position;
	XMFLOAT4 color;
	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	//necessaria per rendering 2D
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
		
	for (index = 0; index < m_ModelList->GetModelCount(); index++)
	{

		m_ModelList->GetData(index, position.x, position.y, position.z, color, cubeRotation);
		// Translate to the location of the sphere.
		translateMatrix = XMMatrixTranslation(position.x, position.y, position.z);
		//cubeRotation = gamestate->getCubeRotationMatrix();

		worldMatrix = XMMatrixMultiply(worldMatrix, cubeRotation);
		worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

		m_Model->Render(m_Direct3D->GetDeviceContext());
		// Render the model using the texture shader.
		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
		if (!result)
		{
			return false;
		}
		// Reset the world matrix.
		m_Direct3D->GetWorldMatrix(worldMatrix);

	}


	/*worldMatrix = XMMatrixMultiply(worldMatrix, cubeRotation);
	//worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_Direct3D->GetDeviceContext());
	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	if (!result)
	{
		return false;
	}
	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);*/

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();
	// Turn on alpha blending.
	m_Direct3D->EnableAlphaBlending();
	// Render the mouse cursor with the texture shader.
	result = m_Bitmap->Render(m_Direct3D->GetDeviceContext(), gamestate->getCurrentMouseX(), gamestate->getCurrentMouseY(), m_FrameCounter);  if (!result) { return false; }
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());

	// Turn off alpha blending.
	m_Direct3D->DisableAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

void GraphicsClass::TestIntersection(GameStateClass* gamestate)
{

	float pointX, pointY;
	XMMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, inverseWorldMatrix;
	XMFLOAT3 direction, origin, rayOrigin, rayDirection;
	bool intersect, result;

	bool debug = false;
	int lastHoverId, lastSelectedId;

	
	float radius;
	int modelCount, index;

	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)gamestate->getCurrentMouseX()) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)gamestate->getCurrentMouseY()) / (float)m_screenHeight) - 1.0f) * -1.0f;

	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	XMFLOAT4X4 fProjectionMatrix;
	XMStoreFloat4x4(&fProjectionMatrix, projectionMatrix);
	//float fProjectionMatrix_11 = fProjectionMatrix._11;
	pointX = pointX / fProjectionMatrix._11;
	pointY = pointY / fProjectionMatrix._22;

	// Get the inverse of the view matrix.
	m_Camera->GetViewMatrix(viewMatrix);
	inverseViewMatrix = XMMatrixInverse(NULL, viewMatrix);
	XMFLOAT4X4 fInverseViewMatrix;
	XMStoreFloat4x4(&fInverseViewMatrix, inverseViewMatrix);

	// Calculate the direction of the picking ray in view space.
	direction.x = (pointX * fInverseViewMatrix._11) + (pointY * fInverseViewMatrix._21) + fInverseViewMatrix._31;
	direction.y = (pointX * fInverseViewMatrix._12) + (pointY * fInverseViewMatrix._22) + fInverseViewMatrix._32;
	direction.z = (pointX * fInverseViewMatrix._13) + (pointY * fInverseViewMatrix._23) + fInverseViewMatrix._33;

	// Get the origin of the picking ray which is the position of the camera.
	origin = m_Camera->GetPosition();

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();
	

	XMFLOAT3 position;
	XMFLOAT4 color;
	XMMATRIX translate;
	XMMATRIX rotate;	
	XMVECTOR originV = XMLoadFloat3(&origin);
	XMVECTOR rayOriginV = XMLoadFloat3(&rayOrigin);
	XMVECTOR rayDirectionV = XMLoadFloat3(&rayDirection);
	XMVECTOR directionV = XMLoadFloat3(&direction);

	//al termine di questo ciclo, il gameState conterrà il closestID() ovvero l'id del cubo su cui è posizionato il mouse
	for (index = 0; index < modelCount; index++)
	{
		// Get the world matrix and translate to the location of the sphere.
		m_Direct3D->GetWorldMatrix(worldMatrix);

		m_ModelList->GetData(index,position.x,position.y,position.z,color, rotate);
		
		// Move the model to the location it should be rendered at.
		translate = XMMatrixTranslation(position.x, position.y, position.z);
		worldMatrix = XMMatrixMultiply(worldMatrix, translate);
		
		// Now get the inverse of the translated world matrix.
		inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);

		// Now transform the ray origin and the ray direction from view space to world space.
		rayOriginV = XMVector3TransformCoord(originV, inverseWorldMatrix);
		rayDirectionV = XMVector3TransformNormal(directionV, inverseWorldMatrix);
		
		// Normalize the ray direction.
		rayDirectionV = XMVector3Normalize(rayDirectionV);		

		// Now perform the ray-sphere intersection test.
		//intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);
		intersect = RayAABBIntersect(debug, gamestate, index, rayOriginV, rayDirectionV, m_Model->getBoundingBox());

	}

}

bool GraphicsClass::RayAABBIntersect(bool debug, GameStateClass* gamestate, int currentid, XMVECTOR rayOriginV, XMVECTOR rayDirectionV, AabbClass* bCube)
{
	//rayOrigin = D3DXVECTOR3(10.0f, 10.0f, -5.0f);
	double tmin = -INFINITY, tmax = INFINITY;


	XMFLOAT4 rayOriginF;
	XMStoreFloat4(&rayOriginF, rayOriginV);
	XMFLOAT4 rayDirectionF;
	XMStoreFloat4(&rayDirectionF, rayDirectionV);

	if (rayDirectionF.x != 0.0) {
		double tx1 = (bCube->min[0] - rayOriginF.x) / rayDirectionF.x;
		double tx2 = (bCube->max[0] - rayOriginF.x) / rayDirectionF.x;

		tmin = max(tmin, min(tx1, tx2));
		tmax = min(tmax, max(tx1, tx2));
	}

	if (rayDirectionF.y != 0.0) {
		double ty1 = (bCube->min[1] - rayOriginF.y) / rayDirectionF.y;
		double ty2 = (bCube->max[1] - rayOriginF.y) / rayDirectionF.y;

		tmin = max(tmin, min(ty1, ty2));
		tmax = min(tmax, max(ty1, ty2));
	}

	if (rayDirectionF.z != 0.0) {
		double tz1 = (bCube->min[2] - rayOriginF.z) / rayDirectionF.z;
		double tz2 = (bCube->max[2] - rayOriginF.z) / rayDirectionF.z;

		tmin = max(tmin, min(tz1, tz2));
		tmax = min(tmax, max(tz1, tz2));
	}

	if (debug == true){
		int ciao = 23;
	}

	//se c'è l'intersezione, e il nuovo oggetto si trova ad una distanza inferiore rispetto a quello correntemente selezionato
	//aggiorna selectionState con le informazioni sul nuovo oggetto
	if ((tmax >= tmin) && (gamestate->getCurrentMinDistance()>tmin)){

		gamestate->setClosestId(currentid);
		gamestate->setCurrentMinDistance(tmin);
		return  true;

	}
	else
		return false;

}

void GraphicsClass::RotateCube(GameStateClass* GameState){


	int selectedID = GameState->getClosestId();
	XMMATRIX cubeRotation = GameState->getCubeRotationMatrix();
	m_mouseX = GameState->getCurrentMouseX();
	m_mouseY = GameState->getCurrentMouseY();
	m_oldMouseX = GameState->getOldMouseX();
	m_oldMouseY = GameState->getOldMouseY();

	XMFLOAT3 axisF = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMVECTOR axisV = XMLoadFloat3(&axisF);

	XMFLOAT3 yaxisF = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMVECTOR yaxisV = XMLoadFloat3(&yaxisF);


	int deltaX, deltaY;

	deltaX = m_mouseX - m_oldMouseX;
	deltaY = m_mouseY - m_oldMouseY;



	//se lo spostamento è maggiore lungo X, allora ruoto su asse Y
	if (abs(deltaX) >= abs(deltaY)){

		//muovo verso dx il mouse
		if (deltaX > 0){

			angle = -0.1f;
			cubeRotation *= XMMatrixRotationAxis(axisV, angle);
		}
		else //muovo verso sx il mouse
			if (deltaX < 0){

				angle = 0.1f;
				cubeRotation *= XMMatrixRotationAxis(axisV, angle);
			}

	}
	else{

		//muovo verso alto il mouse
		if (deltaY > 0){

			angle = -0.1f;
			cubeRotation *= XMMatrixRotationAxis(yaxisV, angle);
		}
		else
			//muovo verso basso il mouse
			if (deltaY < 0){

				angle = 0.1f;
				cubeRotation *= XMMatrixRotationAxis(yaxisV, angle);

			}
	}


	//aggiorno il gamestate
	GameState->setCubeRotationMatrix(cubeRotation);
	GameState->setOldMousePos(m_mouseX, m_mouseY);
}


void GraphicsClass::UpdateCubeColors(GameStateClass* gamestate){

	//prelevo l'id del cubo su cui è posizionato il mouse
	int id = gamestate->getClosestId();

	//se l'intersezione non è vuota
	if (id != -1){

		m_ModelList->SetColor(id,XMFLOAT4(0.5f, 0.6f, 0.34f, 1.0f));
	}



}