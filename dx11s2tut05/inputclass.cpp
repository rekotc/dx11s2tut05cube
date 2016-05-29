// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// input.cpp v1.6
// Last modified Feb-7-2013

#include "inputclass.h"

//=============================================================================
// default constructor
//=============================================================================
InputClass::InputClass()
{
	// clear key down array
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;
	// clear key pressed array
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;
	newLine = true;                     // start new line
	textIn = "";                        // clear textIn
	charIn = 0;                         // clear charIn

	// mouse data
	mouseX = 0;                         // screen X
	mouseY = 0;                         // screen Y
	mouseRawX = 0;                      // high-definition X
	mouseRawY = 0;                      // high-definition Y
	mouseWheel = 0;                     // mouse wheel position
	mouseLButton = false;               // true if left mouse button is down
	mouseMButton = false;               // true if middle mouse button is down
	mouseRButton = false;               // true if right mouse button is down
	mouseX1Button = false;              // true if X1 mouse button is down
	mouseX2Button = false;              // true if X2 mouse button is down

	for (int i = 0; i<MAX_CONTROLLERS; i++)
	{
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;
	}
	thumbstickDeadzone = GAMEPAD_THUMBSTICK_DEADZONE;    // default
	triggerDeadzone = GAMEPAD_TRIGGER_DEADZONE;          // default
}

//=============================================================================
// destructor
//=============================================================================
InputClass::~InputClass()
{
	if (mouseCaptured)
		ReleaseCapture();               // release mouse
}

//=============================================================================
// Initialize mouse and controller input
// Set capture=true to capture mouse
// Throws GameError
//=============================================================================
void InputClass::initialize(HWND hwnd, bool capture)
{
	try{
		mouseCaptured = capture;

		// register high-definition mouse
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

		if (mouseCaptured)
			SetCapture(hwnd);           // capture mouse

		// Clear controllers state
		ZeroMemory(controllers, sizeof(ControllerState) * MAX_CONTROLLERS);

		//checkControllers();             // check for connected controllers
	}
	catch (...)
	{
		//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

//=============================================================================
// Set true in the keysDown and keysPessed array for this key
// Pre: wParam contains the virtual key code (0--255)
//=============================================================================
void InputClass::keyDown(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		keysDown[wParam] = true;    // update keysDown array
		// key has been "pressed, erased by clear()
		keysPressed[wParam] = true; // update keysPressed array
	}
}

//=============================================================================
// Set false in the keysDown array for this key
// Pre: wParam contains the virtual key code (0--255)
//=============================================================================
void InputClass::keyUp(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < inputNS::KEYS_ARRAY_LEN)
		// update state table
		keysDown[wParam] = false;
}

//=============================================================================
// Save the char just entered in textIn string
// Pre: wParam contains the char
//=============================================================================
void InputClass::keyIn(WPARAM wParam)
{
	if (newLine)                            // if start of new line
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')                     // if backspace
	{
		if (textIn.length() > 0)             // if characters exist
			textIn.erase(textIn.size() - 1);  // erase last character entered
	}
	else
	{
		textIn += wParam;                   // add character to textIn
		charIn = wParam;                    // save last char entered
	}

	if ((char)wParam == '\r')               // if return    
		newLine = true;                     // start new line
}

//=============================================================================
// Returns true if the specified VIRTUAL KEY is down, otherwise false.
//=============================================================================
bool InputClass::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

//=============================================================================
// Return true if the specified VIRTUAL KEY has been pressed in the most recent
// frame. Key presses are erased at the end of each frame.
//=============================================================================
bool InputClass::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	else
		return false;
}

//=============================================================================
// Return true if any key was pressed in the most recent frame.
// Key presses are erased at the end of each frame.
//=============================================================================
bool InputClass::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		if (keysPressed[i] == true)
			return true;
	return false;
}

//=============================================================================
// Clear the specified key press
//=============================================================================
void InputClass::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//=============================================================================
// Clear specified input buffers
// See input.h for what values
//=============================================================================
void InputClass::clear(UCHAR what)
{
	if (what & inputNS::KEYS_DOWN)       // if clear keys down
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	if (what & inputNS::KEYS_PRESSED)    // if clear keys pressed
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	if (what & inputNS::MOUSE)           // if clear mouse
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
		mouseWheel = 0;
	}
	if (what & inputNS::TEXT_IN)
	{
		clearTextIn();
		clearCharIn();
	}
}

bool InputClass::readCursorPos(HWND hwnd){

	BOOL result = GetCursorPos(&cursorPosition);

	ScreenToClient(hwnd, &cursorPosition);


	return result;
}

long InputClass::getCursorPosX(){
	
	return cursorPosition.x;
}

long InputClass::getCursorPosY(){

	return cursorPosition.y;
}


//=============================================================================
// Reads mouse screen position into mouseX, mouseY
//=============================================================================
void InputClass::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

//=============================================================================
// Reads raw mouse data into mouseRawX, mouseRawY
// This routine is compatible with a high-definition mouse
//=============================================================================
void InputClass::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
		lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}

//=============================================================================
// Reads mouse wheel movement expressed in multiples of WHEEL_DELTA, which
// is 120. A positive value indicates that the wheel was rotated away from the
// user, a negative value indicates that the wheel was rotated toward the user.
//=============================================================================
void InputClass::mouseWheelIn(WPARAM wParam)
{
	mouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
}


//=============================================================================
// Read state of connected controllers
//=============================================================================
void InputClass::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // if controller disconnected
				controllers[i].connected = false;
		}
	}
}

short InputClass::getMouseLButtonT(){

	return GetAsyncKeyState(VK_LBUTTON);
}
