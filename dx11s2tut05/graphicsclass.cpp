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
	m_LightShader = 0;
	m_Light = 0;

	m_Bitmap = 0;
	m_ModelList = 0;

	m_Background = 0;
	m_Text		= 0;
	m_ConsoleGUI	= 0;


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

	XMMATRIX baseViewMatrix;

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
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

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

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix, 20, 20);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the ConsoleGUI object.
	m_ConsoleGUI = new BitmapClass;
	if (!m_ConsoleGUI)
	{
		return false;
	}

	// Initialize the ConsoleGUI object.
	result = m_ConsoleGUI->InitializeConsoleUI(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, "../data/console-background.tga", 1920, 1080);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the console object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_Background = new BitmapClass;
	if (!m_Background)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Background->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, "../data/violet-game-background.tga", 1920, 1200);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the background object.", L"Error", MB_OK);
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

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);


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

	// Release the model object.
	if (m_ConsoleGUI)
	{
		m_ConsoleGUI->Shutdown();
		delete m_ConsoleGUI;
		m_ConsoleGUI = 0;
	}

	// Release the model object.
	if (m_Background)
	{
		m_Background->Shutdown();
		delete m_Background;
		m_Background = 0;
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

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}


	return;
}


bool GraphicsClass::Frame(GameStateClass* gamestate, int framecounter, ConsoleClass* console)
{
	bool result;
	m_FrameCounter = framecounter;
	
	

	if (m_FrameCounter == 500){

		int ciao = 45;
	}
	
		//test, il lock è true se ho rilasciato la selezione sul cubo
		if (gamestate->getLock()==true){
			int pirla = 34;
		}
		//verifico l'intersezione, a meno che non stia già trascinando un cubo
		if (gamestate->LeftMouseButtonIsDragged() == false){

			int curid = gamestate->getMouseHoverID();
			//se c'è una intersezione ed è diversa da una eventualmente precedente, scrivo il messaggio
			if ( curid != -1 && ( curid != gamestate->getPreviousMouseHoverID()) )
			console->appendMessage("Il mouse e' ora posizionato sul cubo con ID "+std::to_string(gamestate->getMouseHoverID()));
			//verifico se c'è da completare una rotazione
			if (gamestate->getCubeIsBeingRotated()==true){
				console->appendMessage("Devo completare una rotazione sul cubo con ID " + std::to_string(gamestate->getMouseHoverID()));
				CompleteRotation(gamestate, m_ModelList, console);
				gamestate->setCubeIsBeingRotated(false);
					}
			//verifico nuove intersezioni
			TestIntersection(gamestate);
			//aggiorno il colore del cubo in base all'EVENTUALE intersezione trovata.
			UpdateCubeColors(gamestate);
		}
	
	
	//ruoto il cubo EVENTUALMENTE selezionato
	//prima verifico se gamestate ha un cubo selezionato oppure no e se sto trascinando l'oggetto, se NO la funzione non viene chiamata
	if (gamestate->getMouseHoverID() != -1 && gamestate->LeftMouseButtonIsDragged()==true)
		RotateCube(gamestate,m_FrameCounter,console);
	// Render the graphics scene.
	result = Render(gamestate,console);
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(GameStateClass* gamestate, ConsoleClass* console )
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
		
	//BACKGROUND
	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();
	// Turn on alpha blending.
	m_Direct3D->EnableAlphaBlending();
	// Render the mouse cursor with the texture shader.
	result = m_Background->Render(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, m_FrameCounter);  if (!result) { return false; }
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Background->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Background->GetTexture());
		// Turn off alpha blending.
	m_Direct3D->DisableAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();


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
		//result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
		if (gamestate->getMouseHoverID()==0){
			int ciao = 1;

		}
		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_ModelList->GetColor(index));

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
	
	//Visualizza la console dei messaggi
	if (gamestate->getConsoleEnabled()==true){
		//Remder the console background with the texture shader
		result = m_ConsoleGUI->Render(m_Direct3D->GetDeviceContext(), 10, 0, m_FrameCounter);  if (!result) { return false; }
		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_ConsoleGUI->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_ConsoleGUI->GetTexture());
		//recupero il numero totale di messaggi inseriti
		int size = console->getNumberOfMessages();
		int numMess = 0;
		int index = 0;
		//se la coda messaggi è più corta del limite, visualizzero la coda interamente
		if ((MAX_MESSAGES_SHOWN - size) >= 0){
			numMess = size;
			index = 0;
		}
		else{
			//altrimenti visualizzerò tutti i messaggi a partire da index e fino a size
			index = (size - MAX_MESSAGES_SHOWN);
			numMess = size;		
		}
		int posY = 10.0f;

		for (index; index < numMess;index++){
			//Qui devo renderizzare i messaggi d'errore dell'oggetto m_Console
			m_Text->SetMessage(console->getMessage(index), posY, m_Direct3D->GetDeviceContext());
			// Render the text strings.
			result = m_Text->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix);
			if (!result)
			{
				return false;
			}

			//mi sposto un po' più in basso sullo schermo
			posY += 16.0f;
		}
		

	}

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
	XMVECTOR rayOriginV;
	XMVECTOR rayDirectionV = XMLoadFloat3(&rayDirection);
	XMVECTOR directionV = XMLoadFloat3(&direction);

	int curid = gamestate->getMouseHoverID();
	//se c'era qualcosa di selezionato, lo salvo come id precedente, poi lo resetto.
	if ( curid != -1){
		gamestate->setPreviousMouseHoverID(curid);
		resetSelection(gamestate, m_ModelList);
	}


		//al termine di questo ciclo, gamestate->closestID() ovvero l'id del cubo su cui è posizionato il mouse
		for (index = 0; index < modelCount; index++)
		{
			// Get the world matrix and translate to the location of the sphere.
			m_Direct3D->GetWorldMatrix(worldMatrix);

			m_ModelList->GetData(index, position.x, position.y, position.z, color, rotate);

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
	
		//se ho trovato un'intersezione e sto tenendo premuto il mouse, vuol dire che è in atto una rotazione
		if ((gamestate->getMouseHoverID() != -1) && (gamestate->isLeftMouseButtonClicked())){
			//salvo la corrispondente variabile
			gamestate->setCubeIsBeingRotated(true);
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

	if (tmax >= tmin){

		int ciao = 45;
	}

	//se c'è l'intersezione, e il nuovo oggetto si trova ad una distanza inferiore rispetto a quello correntemente selezionato
	//aggiorna selectionState con le informazioni sul nuovo oggetto
	if ((tmax >= tmin) && (gamestate->getCurrentMinDistance()>tmin)){

		gamestate->setMouseHoverID(currentid);
		gamestate->setCurrentMinDistance(tmin);
		return  true;

	}
	else
		return false;

}

void GraphicsClass::RotateCube(GameStateClass* GameState, int framecounter, ConsoleClass* console){


	float angleAroundX = 0.0f;
	float angleAroundY = 0.0f;

	int selectedID = GameState->getMouseHoverID();
	XMMATRIX cubeRotation = m_ModelList->GetRotation(selectedID);
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

	//se lockX && lockY sono entrambi false, calcolo il delta.
	//se deltaX > deltaY lockX = true, altrimenti lockY = true.

	/*
	if (GameState->getLockAroundXAxis() == false && GameState->getLockAroundYAxis() == false){

		if (abs(deltaX) >= abs(deltaY))
			GameState->setLockAroundYAxis(true);
		else
			GameState->setLockAroundXAxis(true);

	}*/


	//switch lockX || lockY, proseguo direttamente a calcolare la rotazione sull'asse appropriato.

	if (GameState->getLockAroundYAxis() == true){

		//muovo verso dx il mouse
		if (deltaX > 0){

			angleAroundY = -0.1f;
			cubeRotation *= XMMatrixRotationAxis(axisV, angleAroundY);
		}
		else //muovo verso sx il mouse
			if (deltaX < 0){

				angleAroundY = 0.1f;
				cubeRotation *= XMMatrixRotationAxis(axisV, angleAroundY);
			}
	}
	

	if (GameState->getLockAroundXAxis() == true){

			if (deltaY > 0){

				angleAroundX = -0.0f;
				cubeRotation *= XMMatrixRotationAxis(yaxisV, angleAroundX);
			}
			else
				//muovo verso basso il mouse
				if (deltaY < 0){

					angleAroundX = 0.0f;
					cubeRotation *= XMMatrixRotationAxis(yaxisV, angleAroundX);

				}
	}
	
	//nella funzione completeRotation devono essere settati a false entrambi i lock.	

	//aggiorno la matrice di rotazione sul singolo modello
	m_ModelList->SetRotation(selectedID, cubeRotation);

	float rotX = m_ModelList->getVariableRotX(selectedID) + angleAroundX;
	float rotY = m_ModelList->getVariableRotY(selectedID) + angleAroundY;

	//devo impedire che l'angolo di rotazione cresca oltre 2pigreco, infatti una rotazione di 2pigreco corrisponde a ZERO gradi
	rotX = (abs(rotX) >= XM_2PI) ? 0.0f : rotX;
	rotY = (abs(rotY) >= XM_2PI) ? 0.0f : rotY;

	//console->appendMessage("Rotazione del cubo " + std::to_string(rotX) + " " + std::to_string(rotY));
	
	m_ModelList->setVariableRotX(selectedID, rotX);
	m_ModelList->setVariableRotY(selectedID, rotY);

	console->appendMessage("variableRotY vale "+std::to_string(rotY));

	if (framecounter >= 1000){

		int ciao = 45;
	}

	//GameState->setCubeRotationMatrix(cubeRotation);
	GameState->setOldMousePos(m_mouseX, m_mouseY);
}


void GraphicsClass::UpdateCubeColors(GameStateClass* gamestate){


	


	if (m_FrameCounter == 500){

		int ciao = 12;
	}

	int id = -1;
	//prelevo l'id del cubo su cui è posizionato il mouse
	id = gamestate->getMouseHoverID();
	XMFLOAT4 hoverColor = XMFLOAT4(0.5f, 0.6f, 0.34f, 1.0f);
	XMFLOAT4 clickColor = XMFLOAT4(0.1f, 0.9f, 0.11f, 1.0f);
	//se l'intersezione non è vuota vuol dire che SICURAMENTE il mouse è posizionato su un oggetto
	if (id != -1){

		//test
		if(gamestate->isLeftMouseButtonClicked() == true)gamestate->setLock(true);

		//se sto trascinando o se ho cliccato su un oggetto
		if (gamestate->LeftMouseButtonIsDragged() == true || gamestate->isLeftMouseButtonClicked()==true){
			m_ModelList->SetColor(id, clickColor);
		}
		//altrimenti ho semplicemente posizionato il mouse sull'oggetto
		else
			m_ModelList->SetColor(id, hoverColor);		
	}

	
}

void GraphicsClass::resetSelection(GameStateClass* gamestate, ModelListClass* modellist){

	//resetto il colore della selezione corrente
	modellist->SetColor(gamestate->getMouseHoverID(), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//resetto id e distanza della selezione corrente
	gamestate->resetMouseHoverID();
	gamestate->resetCurrentMinDistance();
	
	
	

}

void GraphicsClass::CompleteRotation(GameStateClass* gamestate, ModelListClass* modellist, ConsoleClass* console){


	//acquisisco la matrice di rotazione FISSA, che contiene lo stato complessivo delle rotazione FISSE
	//del cubo attualmente selezionato.
	XMMATRIX CubeRotation = modellist->GetFixedRotation(gamestate->getMouseHoverID());
	//cuberotation
	XMFLOAT4X4 fCubeRotation;
	XMStoreFloat4x4(&fCubeRotation, CubeRotation);
	//console->appendMessage("");

	float variableRotY = modellist->getVariableRotY(gamestate->getMouseHoverID());
	float variableRotX = modellist->getVariableRotX(gamestate->getMouseHoverID());
	
	float fixedRotY, fixedRotX;

	//Roba vecchia, controllare

	console->appendMessage("variableRotY vale attualmente "+std::to_string(variableRotY));

	float angles[5] = { 0.0f, XM_PIDIV2, XM_PI, 1.5f*XM_PI, XM_2PI };
	//valore arbitrario ma più grande dei valori ottenibili con calculateDelta();
	float delta = 16 * XM_PI;
	float temp;
	float chosenAngle = 0.0f;
	int sign;
	//ROTAZIONE Y
	//questo ciclo misura la differenza tra l'angolo rotY di rotazione corrente e tutti gli angoli fissi.
	//alla fine del ciclo for, la variabile delta conterrà la minima differenza tra l'angolo rotY di rotazione corrente
	//e l'angolo fisso contenuto in chosenAngle.
	for (int i = 0; i < 5; i++){
		temp = calculateDelta(variableRotY, angles[i]);
		if (temp < delta){
			delta = temp;
			chosenAngle = angles[i];
		}
	}
	
	fixedRotY = (variableRotY >= 0) ? chosenAngle : -chosenAngle;
	console->appendMessage("applico quindi una rotazione a scatto fisso di " + std::to_string(fixedRotY));

	//la matrice fixedRotationMatrix va a sostituire la matrice di rotazione originale ogni qualvolta viene completata una rotazione
	//la matrice fixedRotationMatrix viene quindi aggiornata volta per volta con lo "scatto fisso" di rotazione, e mantiene quindi
	//correttamente lo stato corrente del cubo, inclusivo di tutte le rotazioni a "scatto fisso" precedenti.

	//calcolo l'ulteriore rotazione a "scatto fisso" e la applico a fixedRotationMatrix, che poi andrà a sostituire la matrice originale.

	XMFLOAT3 YaxisF = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMVECTOR YaxisV = XMLoadFloat3(&YaxisF);
	XMFLOAT3 XaxisF = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMVECTOR XaxisV = XMLoadFloat3(&XaxisF);
	//XMMATRIX cubeRotation = XMMatrixIdentity();	

	//cubeRotation *= XMMatrixRotationAxis(YaxisV, rotY);
	//cubeRotation *= XMMatrixRotationAxis(XaxisV, rotX);

	//rotY = +0.3f;
	//rotX = +0.0f;
	//aggiorno le rotazioni globali
	//totalRotY += currentRotY;
	//totalRotX += currentRotX;
	//devo impedire che l'angolo di rotazione cresca oltre 2pigreco, infatti una rotazione di 2pigreco corrisponde a ZERO gradi
	//totalRotX = (abs(totalRotX) >= XM_2PI) ? 0.0f : totalRotX;
	//totalRotY = (abs(totalRotY) >= XM_2PI) ? 0.0f : totalRotY;

	fixedRotX = 0.0f;
	//moltiplico la rotazione corrente per le matrici di rotazione degli angoli appena calcolati
	CubeRotation *= XMMatrixRotationAxis(YaxisV, fixedRotY);
	CubeRotation *= XMMatrixRotationAxis(XaxisV, fixedRotX);
	//aggiorno la matrice di rotazione del cubo, sostituendo alla matrice corrente quella relativa alla rotazione FISSA
	modellist->SetRotation(gamestate->getMouseHoverID(),CubeRotation);
	modellist->SetFixedRotation(gamestate->getMouseHoverID(), CubeRotation);

	modellist->setVariableRotY(gamestate->getMouseHoverID(),0.0f);
	modellist->setVariableRotX(gamestate->getMouseHoverID(),0.0f);		

	gamestate->setLockAroundXAxis(true);
	gamestate->setLockAroundYAxis(true);
}

float GraphicsClass::calculateDelta(float rotation, float angleToCompare){

	return abs(angleToCompare - abs(rotation));

}