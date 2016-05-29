///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "modellistclass.h"


ModelListClass::ModelListClass()
{
	m_ModelInfoList = 0;
}


ModelListClass::ModelListClass(const ModelListClass& other)
{
}


ModelListClass::~ModelListClass()
{
}


bool ModelListClass::Initialize(int numModels)
{
	int i;
	float red, green, blue;


	// Store the number of models.
	m_modelCount = numModels;

	// Create a list array of the model information.
	m_ModelInfoList = new ModelInfoType[m_modelCount];
	if(!m_ModelInfoList)
	{
		return false;
	}

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	// Go through all the models and randomly generate the model color and position.
	for(i=0; i<m_modelCount; i++)
	{
		// Generate a random color for the model.
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		m_ModelInfoList[i].color = XMFLOAT4(red, green, blue, 1.0f);

		// Generate a random position in front of the viewer for the mode.
		m_ModelInfoList[i].positionX = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f;
		m_ModelInfoList[i].positionY = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f;
		m_ModelInfoList[i].positionZ = ((((float)rand()-(float)rand())/RAND_MAX) * 10.0f) + 5.0f;
		m_ModelInfoList[i].id = i;
		m_ModelInfoList[i].rotationMatrix = XMMatrixIdentity();
	}

	return true;
}


void ModelListClass::Shutdown()
{
	// Release the model information list.
	if(m_ModelInfoList)
	{
		delete [] m_ModelInfoList;
		m_ModelInfoList = 0;
	}

	return;
}


int ModelListClass::GetModelCount()
{
	return m_modelCount;
}


void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, XMFLOAT4& color, XMMATRIX& rotationmatrix)
{
	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = m_ModelInfoList[index].color;

	rotationmatrix = m_ModelInfoList[index].rotationMatrix;

	return;
}

void ModelListClass::SetData(int index, float positionX, float positionY, float positionZ){

	m_ModelInfoList[index].positionX = positionX;
	m_ModelInfoList[index].positionY = positionY;
	m_ModelInfoList[index].positionZ = positionZ;

}

void ModelListClass::SetColor(int index, XMFLOAT4 c){

	if (index == -1){
		int ciao = 45;
	}

	m_ModelInfoList[index].color = c;
}

XMFLOAT4 ModelListClass::GetColor(int index){

	return m_ModelInfoList[index].color;
}
/*
AabbClass ModelListClass::getBoundingBox(int index){

	return m_ModelInfoList[index].boundingBox;
}

void ModelListClass::setBoundingBox(int index, AabbClass bb){

	m_ModelInfoList[index].boundingBox = bb;
}
*/

XMMATRIX ModelListClass::GetRotation(int index){

	return m_ModelInfoList[index].rotationMatrix;
}
void ModelListClass::SetRotation(int index, XMMATRIX r){

	m_ModelInfoList[index].rotationMatrix = r;
}