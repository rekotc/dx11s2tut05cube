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
		m_ModelInfoList[i].fixedRotationMatrix = XMMatrixIdentity();

		m_ModelInfoList[i].fixedRotX = 0.0f;
		m_ModelInfoList[i].fixedRotY = 0.0f;
		m_ModelInfoList[i].fixedRotZ = 0.0f;

		m_ModelInfoList[i].variableRotX = 0.0f;
		m_ModelInfoList[i].variableRotY = 0.0f;
		m_ModelInfoList[i].variableRotZ = 0.0f;

		m_ModelInfoList[i].Xaxis = "+x";
		m_ModelInfoList[i].Yaxis = "+y";
		m_ModelInfoList[i].Zaxis = "+z";

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

float ModelListClass::getFixedRotX(int index){
	return m_ModelInfoList[index].fixedRotX;
}
float ModelListClass::getFixedRotY(int index){
	return m_ModelInfoList[index].fixedRotY;
}
float ModelListClass::getFixedRotZ(int index){
	return m_ModelInfoList[index].fixedRotZ;
}

void ModelListClass::setFixedRotX(int index, float r){
	m_ModelInfoList[index].fixedRotX = r;
}
void ModelListClass::setFixedRotY(int index, float r){
	m_ModelInfoList[index].fixedRotY = r;
}
void ModelListClass::setFixedRotZ(int index, float r){
	m_ModelInfoList[index].fixedRotZ = r;
}

void ModelListClass::resetCubeRotation(int index){
	m_ModelInfoList[index].rotationMatrix = XMMatrixIdentity();
}

//qui gestisco vettore di tutte le rotazioni di ogni oggetto
void ModelListClass::appendRotationCode(int index, std::string s){
	m_ModelInfoList[index].rotVector.push_back(s);
}

std::string ModelListClass::getRotationCode(int index, int i){

	return m_ModelInfoList[index].rotVector[i];
}



void ModelListClass::appendRotX(int index, float r){
	m_ModelInfoList[index].rotXVector.push_back(r);
}
float ModelListClass::getRotX(int index, int i){
	return m_ModelInfoList[index].rotXVector[i];
}
void ModelListClass::appendRotY(int index, float r){
	m_ModelInfoList[index].rotYVector.push_back(r);
}
float ModelListClass::getRotY(int index, int i){
	return m_ModelInfoList[index].rotYVector[i];
}
void ModelListClass::appendRotZ(int index, float r){
	m_ModelInfoList[index].rotZVector.push_back(r);
}
float ModelListClass::getRotZ(int index, int i){
	return m_ModelInfoList[index].rotZVector[i];
}

XMMATRIX ModelListClass::GetFixedRotation(int index){

	return m_ModelInfoList[index].fixedRotationMatrix;
}
void ModelListClass::SetFixedRotation(int index, XMMATRIX r){

	m_ModelInfoList[index].fixedRotationMatrix = r;
}

float ModelListClass::getVariableRotX(int index){
	return m_ModelInfoList[index].variableRotX;
}
float ModelListClass::getVariableRotY(int index){
	return m_ModelInfoList[index].variableRotY;
}
float ModelListClass::getVariableRotZ(int index){
	return m_ModelInfoList[index].variableRotZ;
}

void ModelListClass::setVariableRotX(int index, float r){
	m_ModelInfoList[index].variableRotX = r;
}
void ModelListClass::setVariableRotY(int index, float r){
	m_ModelInfoList[index].variableRotY = r;
}
void ModelListClass::setVariableRotZ(int index, float r){
	m_ModelInfoList[index].variableRotZ = r;
}